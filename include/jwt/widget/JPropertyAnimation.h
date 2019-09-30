#ifndef JPROPERTYANIMATION_H
#define JPROPERTYANIMATION_H

#include <QPropertyAnimation>
#include "../global.h"

// - class JPropertyAnimation -

class JPropertyAnimationPrivate;

class JWT_EXPORT JPropertyAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    explicit JPropertyAnimation(QObject *parent = nullptr);
    JPropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = nullptr);
    virtual ~JPropertyAnimation() J_OVERRIDE;

    void restart();
    void restart(const QVariant &endValue);
    void restart(const QVariant &startValue, const QVariant &endValue, int msecs = -1);
    void setRange(const QVariant &startValue, const QVariant &endValue);

private:
    Q_DISABLE_COPY(JPropertyAnimation)
    J_DECLARE_PRIVATE(JPropertyAnimation)
};
#endif // JPROPERTYANIMATION_H
