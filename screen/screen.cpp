#define LOG_TAG "Screen::Screen"
#include "screen.h"
#include "outputmodel.h"
#include "confighandler.h"

#include <kscreen/setconfigoperation.h>

#include <QDataStream>
#include <QFile>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>

#include "elog.h"

Screen::Screen(QObject* parent)
    : QObject(parent)
{
    log_d("Initializing screen Object");
    load();
}

void Screen::load()
{
    // Don't pull away the outputModel under QML's feet
    // signal its disappearance first before deleting and replacing it.
    // We take the m_config pointer so outputModel() will return null,
    // gracefully cleaning up the QML side and only then we will delete it.
    auto* oldConfig = m_config.release();
    if (oldConfig) {
        log_d("Deleting old config");
        emit outputModelChanged();
        delete oldConfig;
    }

    // Create a new config handler and connect it to the outputModelChanged
    log_d("Creating new config");
    m_config.reset(new ConfigHandler(this));
    connect(m_config.get(), &ConfigHandler::outputModelChanged, this, &Screen::outputModelChanged);

    connect(new KScreen::GetConfigOperation(), &KScreen::GetConfigOperation::finished, this, &Screen::configReady);
}

void Screen::save()
{
    if (!m_config)
        return;

    auto config = m_config->config();
    bool atLeastOneEnabledOutput = false;

    for (const KScreen::OutputPtr& output : config->outputs()) {
        KScreen::ModePtr mode = output->currentMode();
        atLeastOneEnabledOutput |= output->isEnabled();
    }

    m_config->writeControl();

    // Store the current config, apply settings. Block until operation is
    // completed, otherwise ConfigModule might terminate before we get to
    // execute the Operation.
    auto* op = new KScreen::SetConfigOperation(config);
    op->exec();
}

OutputModel* Screen::outputModel() const
{
    if (!m_config) {
        log_e("Config not ready");
        return nullptr;
    }

    log_d("Returning outputModel");
    return m_config->outputModel();
}

void Screen::configReady(KScreen::ConfigOperation* op)
{
    log_d("Config ready from KScreen");
    if (op->hasError()) {
        log_e("Error getting config from KScreen: %s", qPrintable(op->errorString()));
        m_config.reset();
        return;
    }

    KScreen::ConfigPtr config = qobject_cast<KScreen::GetConfigOperation*>(op)->config();
    // const bool autoRotationSupported = config->supportedFeatures() & (KScreen::Config::Feature::AutoRotation | KScreen::Config::Feature::TabletMode);

    m_config->setConfig(config);
}
