#ifndef JNOTIFYDIALOG_H
#define JNOTIFYDIALOG_H

#include "../style/JShadowDialog.h"
#include <functional>

class JNotifyDialogPrivate;

class JWT_EXPORT JNotifyDialog : public JShadowDialog
{
    Q_OBJECT
    Q_PROPERTY(QString guid READ guid NOTIFY guidChanged)
    Q_PROPERTY(QString majorText READ majorText NOTIFY majorTextChanged)
    Q_PROPERTY(QString minorText READ minorText NOTIFY minorTextChanged)
public:
    typedef std::function<void(bool/*accepted*/)> CloseCaller;
    typedef std::function<void(bool/*accepted*/)> OpenedCaller;
    typedef std::function<bool()> ConditionCaller;
    typedef std::function<void(std::function<void()>)> BlockingCaller;

    explicit JNotifyDialog(QWidget *parent = nullptr);
    explicit JNotifyDialog(const QString &title, QWidget *parent = nullptr);
    ~JNotifyDialog() J_OVERRIDE;

    QString guid() const;
    QString majorText() const;
    QString minorText() const;

signals:
    void guidChanged(const QString &text);
    void majorTextChanged(const QString &text);
    void minorTextChanged(const QString &text);

public slots:
    void reset();
    void show(const QString &majorText, const QString &minorText, CloseCaller closeCaller,
              bool cancelVisible, const QString &title = QString(), OpenedCaller openedCaller = nullptr,
              const QString &guid = QString());
    void info(const QString &majorText, const QString &minorText, CloseCaller closeCaller,
              bool cancelVisible, const QString &title = QString(), OpenedCaller openedCaller = nullptr,
              const QString &guid = QString());
    void warning(const QString &majorText, const QString &minorText, CloseCaller closeCaller,
                 bool cancelVisible, const QString &title = QString(), OpenedCaller openedCaller = nullptr,
                 const QString &guid = QString());
    void critical(const QString &majorText, const QString &minorText, CloseCaller closeCaller,
                  bool cancelVisible, const QString &title = QString(), OpenedCaller openedCaller = nullptr,
                  const QString &guid = QString());
    void question(const QString &majorText, const QString &minorText, CloseCaller closeCaller,
                  bool cancelVisible, const QString &title = QString(), OpenedCaller openedCaller = nullptr,
                  const QString &guid = QString());
    void await(const QString &majorText, const QString &minorText,
               bool cancelVisible, OpenedCaller openedCaller, ConditionCaller condition,
               int timeout, int delay);
    void blockingShow(const QString &majorText, BlockingCaller callback);

    void setButtonOkVisible(bool visible);

    void accept() override;
    void reject() override;

protected:
    void showEvent(QShowEvent *event) override;

private:

private:
    Q_DISABLE_COPY(JNotifyDialog)
    J_DECLARE_PRIVATE(JNotifyDialog)
};

#endif  // JNOTIFYDIALOG_H
