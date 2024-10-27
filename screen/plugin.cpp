#include <QQmlExtensionPlugin>
#include <QQmlEngine>

#include "outputmodel.h"
#include "screen.h"

class QmlPlugins : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char * uri) override {
        qmlRegisterAnonymousType<OutputModel>(uri, 1);
        qmlRegisterType<Screen>(uri, 1, 0, "Screen");
        qmlRegisterType<KScreen::Output>(uri, 1, 0, "Output");
    }
};

#include "plugin.moc"