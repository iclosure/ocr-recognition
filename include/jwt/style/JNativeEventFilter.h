#ifndef JNATIVEEVENTFILTER_H
#define JNATIVEEVENTFILTER_H

#include "../global.h"
#include <QWidget>
#include <QAbstractNativeEventFilter>
#include <QWindow>

// class JNativeEventFilter

class JNativeEventFilterPrivate;

class JWT_EXPORT JNativeEventFilter : public QAbstractNativeEventFilter
{
public:
    explicit JNativeEventFilter(WId target = 0);
    ~JNativeEventFilter() J_OVERRIDE;

    bool resizable() const;
    void setResizable(bool enabled);

    void setSysMenuEnabled(bool enabled);
    void setMinimizable(bool enabled);
    void setMaximizable(bool enabled);
    void setClosable(bool enabled);

    static bool enableShadow(WId winId, bool enabled = true, bool thick = true);

    // QAbstractNativeEventFilter interface
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
    bool winEventFilter(void *message, long *result);

private:
    Q_DISABLE_COPY(JNativeEventFilter)
    J_DECLARE_PRIVATE(JNativeEventFilter)
};

#endif  // JNATIVEEVENTFILTER_H
