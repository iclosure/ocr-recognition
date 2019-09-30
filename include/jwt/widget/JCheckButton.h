#ifndef JCHECKBUTTON_H
#define JCHECKBUTTON_H

#include "../global.h"
#include <QPushButton>

class JCheckButtonPrivate;

class JWT_EXPORT JCheckButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
public:
    explicit JCheckButton(QWidget *parent = nullptr);
    explicit JCheckButton(const QString &title, QWidget *parent = nullptr);
    ~JCheckButton() J_OVERRIDE;

    qreal scale() const;

Q_SIGNALS:
    void scaleChanged(qreal value);

private Q_SLOTS:
    void setScale(qreal value, bool animation = false);

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    Q_DISABLE_COPY(JCheckButton)
    J_DECLARE_PRIVATE(JCheckButton)
};

#endif  // JCHECKBUTTON_H
