#include <QQmlExtensionPlugin>
#include <QQmlEngine>



class QmlPlugins : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char * uri) override {

    }
};

#include "logger_plugin.moc"
