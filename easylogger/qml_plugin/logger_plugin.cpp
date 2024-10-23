#include <QQmlEngine>
#include <QQmlExtensionPlugin>

#include "LingmoLogger.h"

class QmlPlugins : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char* uri) override
    {
        qmlRegisterSingletonType<LingmoLogger>(uri, 1, 0, "LingmoLogger",
            [](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject* {
                Q_UNUSED(scriptEngine)
                QObject* instance = LingmoLogger::getInstance();
                engine->setObjectOwnership(instance, QQmlEngine::CppOwnership);
                return instance;
            });
    }
};

#include "logger_plugin.moc"
