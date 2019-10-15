#ifndef global_H
#define global_H

#include "jwt/JNotify.h"
#include "jwt/3rdpart/jsoncpp/json_tool.h"
#include <QObject>
#include <QStandardItem>
#include <QEvent>
#include <memory>

namespace J {
class Item;
typedef std::shared_ptr<Item> ItemPtr;
class Parser;
typedef std::shared_ptr<Parser> ParserPtr;
}

class JNEvent;
class JNotify;
typedef std::shared_ptr<JNotify> JNotifyPtr;

// class JMain

class QWidget;
class JMainPrivate;
class MainWindow;

class JMain : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QString printerName READ printerName WRITE setPrinterName NOTIFY printerNameChanged)
public:
    enum ViewType {
        PreferenceView,
        MonitorView
    };
    Q_ENUM(ViewType)

    bool init();

    QString configDir() const;
    QString configFile() const;

    QString theme() const;
    QString printerName() const;

    static bool initTranslators();
    static bool initFontDatabase();
    static QWidget *createMainWindow();
    static int execApp(QApplication *app);

    static int appVerMajor();
    static int appVerMinor();
    static int appVerPatch();
    static int appVerBuild();
    static QString appVersion();

    void registerSingletonRelease(SingletonReleaseCallback callback);

    static bool initAppPath();
    static QString appDirPath();

    void setRestartFlag(bool neeedToRestart);
    bool isNeedToRestart() const;

    MainWindow *mainWindow() const;

    JNotifyPtr notify();
    const JNotifyPtr &notify() const;

    Json::Value config(const QString &path) const;
    bool setConfig(const QString &path, const Json::Value &config);
    Json::Value option(const QString &module) const;
    Json::Value option(const QString &module, const QString &key) const;
    bool setOption(const QString &module, const Json::Value &option);
    bool setOption(const QString &module, const QString &key, const Json::Value &option);

    J::ParserPtr parser(const QString &module) const;

    static QStringList modules();

signals:
    void themeChanged(const QString &currnt, const QString &previous);
    void printerNameChanged(const QString &currnt, const QString &previous);

public slots:
    void setTheme(const QString &value);
    void setPrinterName(const QString &text);

private:
    explicit JMain(QObject *parent = nullptr);
    ~JMain();

private:
    Q_DISABLE_COPY(JMain)
    J_DECLARE_PRIVATE(JMain)
    J_DECLARE_SINGLE_INSTANCE(JMain)
};

// class Serializable

class Serializable
{
public:
    virtual ~Serializable() {}
    virtual QJsonObject save() const = 0;
    virtual void restore(const QJsonObject &/*json*/) = 0;
};

//
#ifdef jnotify
#undef jnotify
#endif
#define jnotify JMain::instance()->notify()

#endif // global_H
