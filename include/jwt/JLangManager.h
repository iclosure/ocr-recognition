#ifndef JLANGMANAGER_H
#define JLANGMANAGER_H

#include "global.h"
#include <QObject>

class JLangManagerPrivate;
class QTranslator;
class QLocale;

class JWT_EXPORT JLangManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString localeName READ localeName WRITE setLocaleName NOTIFY localeNameChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
public:
    explicit JLangManager(QObject *parent = nullptr);
    ~JLangManager() J_OVERRIDE;

    static QStringList localeNames();
    static QStringList languages();
    QLocale locale() const;
    QString localeName() const;
    QString language() const;

    bool installTranslator(const QString &prefix = QString());
    bool installTranslators(const QString &localeName, const QString &prefix = QString());
    void removeTranslators();

    static bool parseLanguage(QLocale &locale, const QString &language);
    static bool loadTranslator(QTranslator *&translator, const QLocale &locale,
                               const QString qrcPrefix, const QString &prefix,
                               bool useLocale = false);
    static void unloadTranslator(QTranslator *&translator);

    QString localeLanguage() const;
    static QString localeLanguage(const QString &language);
    static QString localeLanguageByLocaleName(const QString &localeName);
    static QString localeName(const QString &language);
    static QString language(const QString localeName);

signals:
    void localeNameChanged(const QString &localeName);
    void languageChanged(const QString &language);

public slots:
    void setLocaleName(const QString &localeName);
    void setLanguage(const QString &language);

private:
    Q_DISABLE_COPY(JLangManager)
    J_DECLARE_PRIVATE(JLangManager)
    J_DECLARE_SINGLE_INSTANCE(JLangManager)
};

#endif // JLANGMANAGER_H
