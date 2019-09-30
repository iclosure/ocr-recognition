#ifndef JPROGRESSDILOG_H
#define JPROGRESSDILOG_H

#include "jwt/style/JShadowDialog.h"
#include <QFuture>
#include "global.h"

namespace J {

class JProgressDialogPrivate;

class PROTOWIDGET_EXPORT JProgressDialog : public JShadowDialog
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    Q_PROPERTY(int progressValue READ progressValue WRITE setProgressValue NOTIFY progressValueChanged)
    Q_PROPERTY(bool progressVisible READ progressVisible WRITE setProgressVisible NOTIFY progressVisibleChanged)
    Q_PROPERTY(QString acceptText READ acceptText WRITE setAcceptText NOTIFY acceptTextChanged)
    Q_PROPERTY(bool acceptVisible READ acceptVisible WRITE setAcceptVisible NOTIFY acceptVisibleChanged)
    Q_PROPERTY(QString cancelText READ cancelText WRITE setCancelText NOTIFY cancelTextChanged)
    Q_PROPERTY(bool cancelVisible READ cancelVisible WRITE setCancelVisible NOTIFY cancelVisibleChanged)
public:
    explicit JProgressDialog(QWidget *parent = nullptr);
    ~JProgressDialog() J_OVERRIDE;

    QString message() const;
    int progressMinimum() const;
    int progressMaximum() const;
    int progressValue() const;
    bool progressVisible() const;
    QString acceptText() const;
    bool acceptVisible() const;
    QString cancelText() const;
    bool cancelVisible() const;

    void waitForFinished();
    void setFuture(const QFuture<bool> &future);
    bool isCanceled() const;
    bool futureResult() const;

    void setInvertedAppearance(bool invert);
    bool invertedAppearance() const;

Q_SIGNALS:
    void messageChanged(const QString &message);
    void progressValueChanged(int value);
    void progressVisibleChanged(bool visible);
    void acceptTextChanged(const QString &text);
    void acceptVisibleChanged(bool visible);
    void cancelTextChanged(const QString &text);
    void cancelVisibleChanged(bool visible);
    void canceled();
    void finished();

public Q_SLOTS:
    void setMessage(const QString &message);
    void setProgressRange(int minimum, int maximum);
    void setProgressValue(int value);
    void setProgressVisible(bool visible);
    void setAcceptText(const QString &text);
    void setAcceptVisible(bool visible);
    void setCancelText(const QString &text);
    void setCancelVisible(bool visible);

private:
    Q_DISABLE_COPY(JProgressDialog)
    J_DECLARE_PRIVATE(JProgressDialog)
};

} // end of namespace J

#endif // JPROGRESSDILOG_H
