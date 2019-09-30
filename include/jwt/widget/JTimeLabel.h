#ifndef JTIMELABEL_H
#define JTIMELABEL_H

#include <QLabel>
#include "../global.h"

class JTimeLabelPrivate;

class JWT_EXPORT JTimeLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QString format READ format WRITE setFormat NOTIFY formatChanged)
public:
    explicit JTimeLabel(QWidget *parent = nullptr);
    ~JTimeLabel() J_OVERRIDE;

    QString format() const;

Q_SIGNALS:
    void formatChanged(const QString &format);

public Q_SLOTS:
    void setFormat(const QString &format);

    void start();
    void stop();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    Q_DISABLE_COPY(JTimeLabel)
    J_DECLARE_PRIVATE(JTimeLabel)
};

#endif  // JTIMELABEL_H
