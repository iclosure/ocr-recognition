#include "global.h"
#include "common/Logging.h"
#include "SplashWidget.h"
#include "mainview/MainWindow.h"
#include "jwt/JLangManager.h"
#include <QFileSystemWatcher>
#include <QApplication>
#include <QSettings>
#include <QSharedMemory>
#include <QDir>
#include <QFontDatabase>
#include <QMessageBox>
#include <QProcess>
#include <QScreen>
#include <QtPrintSupport/QPrinterInfo>
#include <QDebug>

// class JMainPrivate

class JMainPrivate
{
public:
    JMainPrivate(JMain *q)
        : J_QPTR(q)
        , sharedMemory(QStringLiteral("%1-%2").arg(QCoreApplication::applicationName())
                       .arg(JMain::appVersion()))
        , notify(nullptr)
        , neeedToRestart(false)
        , mainWindow(nullptr)
    {
        const QString fileName(QLatin1String("main.json"));
        QSettings settings;
        settings.beginGroup(QCoreApplication::applicationVersion().append(QLatin1String("/Temp/Paths")));
        configDir = settings.value(QLatin1String("CONFIG_DIR")).toString();
#if 0
        const QString homeDir = settings.value(QLatin1String("HOME_DIR")).toString();
        configFile = homeDir + QLatin1String("/~") + fileName;
#else
        configFile = configDir + QLatin1String("/~") + fileName;
#endif
        settings.setValue(QLatin1String("CONFIG_FILE"), configFile);
        settings.endGroup();
        //
        const bool isRunning = this->isRunning();
        if (isRunning) {
            qWarning().noquote() << QStringLiteral("Warning: another \"%1\" is running!")
                                    .arg(sharedMemory.key());
        }
        // create temporary config
        if (!QFile::exists(configFile)) {
            QFile::copy(configDir + QLatin1String("/") + fileName, configFile);
            // replace config
            QFile file(configFile);
            if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QByteArray content = file.readAll();
                if (!content.isEmpty()) {
                    content = Jwt::replaceConfig(content, false);
                    file.resize(0);
                    file.write(content);
                    file.flush();
                    content.clear();
                }
                file.close();
            } else {
                qCritical().noquote() << QStringLiteral("File \"%1\" open failure!").arg(configFile);
            }
        }
    }

    ~JMainPrivate()
    {
#if 1
        // save config
        if (!isRunning()) {
            const QString oldConfigFile = configDir + QLatin1String("/main.json");
            if (QFile::exists(configFile)) {
                QFile file(configFile);
                if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    QByteArray content = file.readAll();
                    if (!content.isEmpty()) {
                        content = Jwt::replaceConfig(content, true);
                        file.resize(0);
                        file.write(content);
                        file.flush();
                        content.clear();
                    }
                    file.close();
                    QFile::remove(oldConfigFile);
                    QFile::rename(configFile, oldConfigFile);
                }
            }
        }
#endif
    }

    void init();
    bool isRunning();
    bool isConfigFileExists() const;
    static bool setStyleSheet(const QString &filePath);

    void clearFiles(const QString &path);
    void clearPath(const QString &path);

private:
    J_DECLARE_PUBLIC(JMain)
    QSharedMemory sharedMemory;
    JNotifyPtr notify;
    QList<SingletonReleaseCallback> callbacks;
    QString configDir;
    QString configFile;
    bool neeedToRestart;
    MainWindow *mainWindow;
    static QString appDirPath;
};

QString JMainPrivate::appDirPath = QString();

void JMainPrivate::init()
{
    Q_Q(JMain);
    notify = JNotifyPtr(JNotify::inst(QCoreApplication::applicationName(), q));
    Q_ASSERT(notify != nullptr);
    //
    notify->on(QLatin1String("app.theme"), q, [=](JNEvent &event){
        q->setTheme(event.argument().toString());
    });
}

bool JMainPrivate::isRunning()
{
#if defined(WIN32)
    if (sharedMemory.attach(QSharedMemory::ReadOnly)) {
        sharedMemory.detach();
    }

    if (!sharedMemory.create(1, QSharedMemory::ReadOnly)) {
        qDebug().noquote() << sharedMemory.error() << QLatin1String(", ")
                           << sharedMemory.errorString();
        return true;
    }

    return false;
#elif defined(__APPLE__)
    return false;   //TODO
#elif defined(__linux)
    if (sharedMemory.attach(QSharedMemory::ReadOnly)) {
        sharedMemory.detach();
    }

    if (!sharedMemory.create(1, QSharedMemory::ReadOnly)) {
        qDebug().noquote() << sharedMemory.error() << QLatin1String(", ")
                           << sharedMemory.errorString();
        return true;
    }

    return false;
#else
#error not supported platform!
    return false;
#endif
}

bool JMainPrivate::isConfigFileExists() const
{
    return QFile::exists(configFile);
}

bool JMainPrivate::setStyleSheet(const QString &filePath)
{
    QFile file(filePath);
    if (!file.exists()) {
        qWarning().noquote() << QLatin1String("File") << filePath << QLatin1String("is not exists!");
        return false;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    qApp->setStyleSheet(file.readAll());

    return true;
}

void JMainPrivate::clearFiles(const QString &path)
{
    QDir dir(path);
    dir.setFilter(QDir::Files);
    const int fileCount = int(dir.count());
    for (int i = 0; i < fileCount; i++) {
        dir.remove(dir[i]);
    }
}

void JMainPrivate::clearPath(const QString &path)
{
    QDir dir(path);
    QFileInfoList fileInfos = dir.entryInfoList(QDir::Dirs | QDir::Files
                                                | QDir::Readable | QDir::Writable
                                                | QDir::Hidden | QDir::NoDotAndDotDot);
    foreach (const auto &fileInfo, fileInfos) {
        if(fileInfo.isFile()) {
            QFile fileTemp(fileInfo.filePath());
            fileTemp.remove();
        } if (fileInfo.isDir()) {
            clearPath(fileInfo.filePath());
        }
    }

    dir.rmdir(".");
}

// class JMain

J_IMPLEMENT_SINGLE_INSTANCE(JMain, JMain)

JMain::JMain(QObject *parent)
    : QObject(parent)
    , J_DPTR(new JMainPrivate(this))
{
    Q_D(JMain);
    d->init();
}

JMain::~JMain()
{
    Q_D(JMain);
    foreach (auto &callback, d->callbacks) {
        if (callback) {
            callback();
        }
    }
    delete d;
}

QString JMain::configFile() const
{
    Q_D(const JMain);
    return d->configFile;
}


QString JMain::theme() const
{
    Json::Value themeJson = Json::resolve(configFile().toLocal8Bit().data(), "global.theme");
    if (themeJson.isNull()) {
        return QString();
    }

    return QString::fromStdString(themeJson["name"].asString());
}

QString JMain::printerName() const
{
    Json::Value printerJson = Json::resolve(configFile().toLocal8Bit().data(), "global.printer");
    if (printerJson.isNull()) {
        return QString();
    }

    return QString::fromStdString(printerJson["name"].asString());
}

bool JMain::initTranslators()
{
    bool result = true;
    //
    result = result && JLangManager::instance()->installTranslator(QLatin1String("desktop"));
    if (!result) {
        return false;
    }
    //
    const QString localeName = JLangManager::instance()->localeName();
    QSettings settings;
    settings.beginGroup(Jwt::settingsGroupPrefix(QLatin1String("Settings")));
    settings.setValue(QLatin1String("localeName"), localeName);
    settings.endGroup();
    //
    result = result && Jwt::instance()->setLocaleName(localeName);

    return result;
}

bool JMain::initFontDatabase()
{
    // fonts
    QDir fontDir(instance()->configDir().append(QLatin1String("/fonts")));
    QStringList fontFiles = fontDir.entryList(QStringList() << QLatin1String("*.ttf") << QLatin1String("*.otf"),
                                              QDir::NoDotAndDotDot | QDir::Files
                                              | QDir::NoSymLinks | QDir::Readable);
    foreach (auto &font, fontFiles) {
        int result = QFontDatabase::addApplicationFont(fontDir.path() + QLatin1String("/") + font);
        if (result <= 0) {
            //qDebug() << "addFont:" << result;
        }
    }

    return true;
}

QWidget *JMain::createMainWindow()
{
    MainWindow *mainWindow = new MainWindow();

    QScreen *screen = QApplication::primaryScreen();
    mainWindow->resize(int(screen->geometry().width() * 0.7),
                       int(screen->geometry().height() * 0.75));
    mainWindow->init();

    instance()->d_func()->mainWindow = mainWindow;

    return mainWindow;
}

int JMain::execApp(QApplication *app)
{
    if (!app) {
        return -1;
    }

    //
    const QString theme = JMain::instance()->theme();
#if defined(TEST_STYLESHEET)
    const QString prefix(PROJECT_DIR + QLatin1String("/src/resource/qss/"));
    const QString filePath(prefix + theme + QLatin1String(".qss"));
    if (QFile(filePath).exists()) {
        JMainPrivate::setStyleSheet(filePath);
        QFileSystemWatcher *fileSysWatcher = new QFileSystemWatcher(JMain::instance());
        fileSysWatcher->addPath(filePath);
        QObject::connect(fileSysWatcher, &QFileSystemWatcher::fileChanged,
                         [=](const QString &_filePath){
            JMainPrivate::setStyleSheet(_filePath);
        });
        QObject::connect(JMain::instance(), &JMain::themeChanged,
                         [=](const QString &currnt, const QString &previous){
            QString _filePath(prefix + previous + QLatin1String(".qss"));
            fileSysWatcher->removePath(_filePath);
            _filePath = prefix + currnt + QLatin1String(".qss");
            fileSysWatcher->addPath(_filePath);
            JMainPrivate::setStyleSheet(_filePath);
        });
    } else {
        JMain::instance()->setTheme(theme);
    }
#else
    JMain::instance()->setTheme(theme);
#endif
    initFontDatabase();
    Logging::instance()->init();

    auto releaseInstances = [=](){
        Logging::releaseInstance();
        JMain::releaseInstance();
    };
    // initialize models
    bool result = instance()->init();
    if (!result) {
        QMessageBox::critical(nullptr, QStringLiteral("Error"),
                              QStringLiteral("global config initialize failure!"));
        releaseInstances();
        return -1;
    }
    // mainWindow
    auto mainWindow = createMainWindow();
    if (!mainWindow) {
        delete mainWindow;
        mainWindow = nullptr;
        releaseInstances();
        return -1;
    }

    mainWindow->showNormal();

    jnotify->on(QLatin1String("main.mainwindow.inst"), JMain::instance(), [=](JNEvent &event){
        event.setReturnValue(QVariant::fromValue<void*>(mainWindow));
    });

    int exitCode = app->exec();

    delete mainWindow;
    mainWindow = nullptr;

    //
    if (instance()->isNeedToRestart()) {
        QProcess::startDetached(QCoreApplication::applicationFilePath(),
                                QStringList(), QCoreApplication::applicationDirPath());
    }

    releaseInstances();

    return exitCode;
}

int JMain::appVerMajor()
{
    QString version = appVersion();
    if (version.isEmpty()) {
        return -1;
    }

    return version.section('.', 0, 0).toInt();
}

int JMain::appVerMinor()
{
    QString version = appVersion();
    if (version.isEmpty()) {
        return -1;
    }

    return version.section('.', 1, 1).toInt();
}

int JMain::appVerPatch()
{
    QString version = appVersion();
    if (version.isEmpty()) {
        return -1;
    }

    return version.section('.', 2, 2).toInt();
}

int JMain::appVerBuild()
{
    QString version = appVersion();
    if (version.isEmpty()) {
        return -1;
    }

    return version.section('.', 3, 3).toInt();
}

QString JMain::appVersion()
{
    QString s = appDirPath();
    QFile file(appDirPath() + QLatin1String("/../VERSION"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }

    return file.readLine(20).trimmed();
}

void JMain::registerSingletonRelease(SingletonReleaseCallback callback)
{
    if (!callback) {
        return;
    }

    Q_D(JMain);
    if (d->callbacks.contains(callback)) {
        return;
    }

    return d->callbacks.append(callback);
}

bool JMain::initAppPath()
{
    QString appDir = QCoreApplication::applicationDirPath();
#if defined(__APPLE__)
    appDir = QDir(appDir + QLatin1String("/../../..")).canonicalPath();
#else
    //
#endif

    JMainPrivate::appDirPath = appDir;

    return true;
}

QString JMain::appDirPath()
{
    return JMainPrivate::appDirPath;
}

void JMain::setRestartFlag(bool neeedToRestart)
{
    Q_D(JMain);
    d->neeedToRestart = neeedToRestart;
}

bool JMain::isNeedToRestart() const
{
    Q_D(const JMain);
    return d->neeedToRestart;
}

MainWindow *JMain::mainWindow() const
{
    Q_D(const JMain);
    return d->mainWindow;
}

JNotifyPtr JMain::notify()
{
    Q_D(JMain);
    return d->notify;
}

const JNotifyPtr &JMain::notify() const
{
    Q_D(const JMain);
    return d->notify;
}

Json::Value JMain::config(const QString &path) const
{
    return Json::resolve(configFile().toStdString(), path.toStdString());
}

bool JMain::setConfig(const QString &path, const Json::Value &config)
{
    return Json::make(configFile().toStdString(), path.toStdString(), config,
                      false, false);
}

Json::Value JMain::option(const QString &module) const
{
    return config(QLatin1String("module.") + module);
}

Json::Value JMain::option(const QString &module, const QString &key) const
{
    return config(QLatin1String("module.") + module + '.' + key);
}

bool JMain::setOption(const QString &module, const Json::Value &option)
{
    return setConfig(QLatin1String("module.") + module, option);
}

bool JMain::setOption(const QString &module, const QString &key, const Json::Value &option)
{
    return setConfig(QLatin1String("module.") + module + '.' + key, option);
}

J::ParserPtr JMain::parser(const QString &module) const
{
    if (module.isEmpty()) {
        return J::ParserPtr();
    }

    J::ParserPtr parser;
    if (!jnotify->send(module + QLatin1String(".parser.inst"),
                       QVariant::fromValue<void*>(&parser)).toBool()
            || !parser) {
        return J::ParserPtr();
    }

    return parser;
}

QStringList JMain::modules()
{
    QStringList _modules;
    _modules << QLatin1String("monitor");
    return _modules;
}

QString JMain::tessdataDir()
{
    return QCoreApplication::applicationDirPath().append(QLatin1String("/../tessdata"));
}

void JMain::setTheme(const QString &text)
{
    const QString previous = theme();
    if (!setConfig(QLatin1String("global.theme.name"), Json::Value(text.toStdString()))) {
        return;
    }

    if (text == QLatin1String("none")) {
        qApp->setStyleSheet(QString());
    } else {
        const QString filePath(QLatin1String(":/desktop/qss/") + text + QLatin1String(".qss"));
        if (!QFile::exists(filePath)) {
            qWarning() << QLatin1String("Theme \"") << text << QLatin1String("\" is invalid!");
            return;
        }
        JMainPrivate::setStyleSheet(filePath);
    }

    emit themeChanged(text, previous);

    jnotify->post(QLatin1String("global.theme.changed"), text);
}

void JMain::setPrinterName(const QString &text)
{
    const QString previous = printerName();
    if (!setConfig(QLatin1String("global.printer.name"), Json::Value(text.toStdString()))) {
        return;
    }

    QStringList printerNames = QPrinterInfo::availablePrinterNames();
    if (printerNames.contains(text)) {
        //
    } else {
        //
    }

    emit printerNameChanged(text, previous);
}

bool JMain::init()
{
    bool result = true;

    //result = result && ExcelProcess::instance()->init();

    return result;
}

QString JMain::configDir() const
{
    Q_D(const JMain);
    return d->configDir;
}
