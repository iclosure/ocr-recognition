#include "global.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFontDatabase>
#include <QSettings>
#include <QDateTime>
#include <QIcon>
#include <QMessageBox>

int main(int argc, char **argv)
{
    qsrand(uint(QDateTime::currentMSecsSinceEpoch()));

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
#ifdef _MSC_VER
#if QT_VERSION >= 0x050600
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#endif
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    //QApplication::setAttribute(Qt::AA_DontUseNativeDialogs);

    QApplication app(argc, argv);

    {
        JMain::initAppPath();
#if 0
        // fonts
        const QString _fontPath = QFileInfo(QCoreApplication::applicationDirPath()
                                            + "/../config/fonts/").canonicalFilePath();
        QDir fontDir(_fontPath);
        if (fontDir.exists()) {
            QStringList fontFiles = fontDir.entryList(QStringList() << "*.ttf" << "*.otf",
                                                      QDir::NoDotAndDotDot | QDir::Files
                                                      | QDir::NoSymLinks | QDir::Readable);
            foreach (auto &font, fontFiles) {
                int result = QFontDatabase::addApplicationFont(fontDir.path() + "/" + font);
                if (result <= 0) {
                    //qDebug() << "addFont:" << result;
                }
            }
        }
#endif
#ifdef _MSC_VER
        QApplication::setFont(QFont(QLatin1String("Microsoft YaHei"), 10));
        //QApplication::setFont(QFont("Noto Sans S Chinese Bold", 12));
#endif
        QApplication::setWindowIcon(QIcon(QLatin1String(":/desktop/image/favicon.png")));
        QCoreApplication::setOrganizationName(QLatin1String("Smartsoft"));
        QCoreApplication::setApplicationName(QLatin1String("OCR-DevInfo"));
        QCoreApplication::setApplicationVersion(QStringLiteral("%1.%2.%3")
                                                .arg(JMain::appVerMajor())
                                                .arg(JMain::appVerMinor())
                                                .arg(JMain::appVerPatch()));
        // settings
        QSettings settings;
        settings.beginGroup(QCoreApplication::applicationVersion().append(QLatin1String("/Temp/Paths")));
        QString appDir = JMain::appDirPath();
#ifdef DEBUG
        QString projectDir(PROJECT_DIR);
        if (!QDir(projectDir).exists()) {
            projectDir = appDir + QLatin1String("/..");
        }
#else
        QString projectDir = appDir + QLatin1String("/..");
#endif
        projectDir = QDir(projectDir).canonicalPath();
        //
        const QString homeDir(QDir::homePath() + QLatin1String("/.ocr-devinfo"));
#if 0
        QDir dirHome(homeDir);
        if (!dirHome.exists()) {
            dirHome.mkpath(homeDir);
        }
#endif
        //
        settings.setValue(QLatin1String("APP_DIR"), appDir);
        settings.setValue(QLatin1String("THIS_DIR"), projectDir);
        settings.setValue(QLatin1String("CONFIG_DIR"),
                          QDir(projectDir + QLatin1String("/config")).canonicalPath());
        settings.setValue(QLatin1String("HOME_DIR"), homeDir);
        settings.setValue(QLatin1String("WORKSPACE_DIR"),
                          QDir(projectDir + QLatin1String("/example")).canonicalPath());
        settings.endGroup();
        //
        //Jwt::cleanTempFiles();
        //
        if (!JMain::initTranslators()) {
            QMessageBox::warning(nullptr, QObject::tr("Warning"),
                                 QObject::tr("Initialize translators failure!"));
        }

        //J::initialize();

        QApplication::setApplicationDisplayName(QObject::tr("OCR-DevInfo")
                                                + ' ' + QCoreApplication::applicationVersion());

    }

    int ret = JMain::execApp(&app);

    //J::uninitialize();

    return ret;
}
