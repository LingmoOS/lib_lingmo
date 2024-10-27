#pragma once

#include <QObject>
#include <kscreen/getconfigoperation.h>
#include <memory>

#include "lingmoscreen_qmlplugins_export.h"

#include "confighandler.h"
#include "outputmodel.h"
class LINGMOSCREEN_QMLPLUGINS_EXPORT Screen : public QObject {
    Q_OBJECT
    Q_PROPERTY(OutputModel* outputModel READ outputModel NOTIFY outputModelChanged)

public:
    explicit Screen(QObject* parent = nullptr);

    OutputModel* outputModel() const;

    void load();
    Q_INVOKABLE void save();

private:
    void configReady(KScreen::ConfigOperation* op);

Q_SIGNALS:
    /**
     * @brief outputModelChanged
     * @details This signal is emitted when the output model is changed.
     *    Also, the output model is ONLY available after this signal is emitted.
     *    You will get a nullptr if this signal is not emitted, as the model
     *    is being initialized.
     * @since 1.0
     */
    void outputModelChanged();

private:
    std::unique_ptr<ConfigHandler> m_config;
};