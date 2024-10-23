#include <QQmlEngine>
#include <QQmlExtensionPlugin>

#include "LingmoLogger.h"

class QmlPlugins : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char* uri) override
    {
        //@uri Lingmo.Logger
        qmlRegisterSingletonType<LingmoLogger>(uri, 1, 0, "LingmoLogger",
            [](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject* {
                Q_UNUSED(scriptEngine)
                QObject* instance = LingmoLogger::getInstance();
                engine->setObjectOwnership(instance, QQmlEngine::CppOwnership);
                return instance;
            });
    }

    void initializeEngine(QQmlEngine* engine, const char* uri) override {
        Q_UNUSED(uri)
        Q_UNUSED(engine)
    }
};

#include "logger_plugin.moc"
