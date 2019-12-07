#ifndef STORABLEPROXY_H
#define STORABLEPROXY_H

#include "global.h"

// JStorableProxy

class JStorableProxyPrivate;

class JWT_EXPORT JStorableProxy
{
public:
    explicit JStorableProxy(const QString &group);
    virtual ~JStorableProxy();

    QString group() const;
    void setGroup(const QString &text);

    virtual QVariant readValue(const QString &key, const QVariant &defaultValue = QVariant()) const;
    template<typename T> inline
    T readValue(const QString &key, const QVariant &defaultValue = QVariant()) const
    { return readValue(key, defaultValue).value<T>(); }
    virtual void writeValue(const QString &key, const QVariant &value) const;

    virtual void clearValue() const;

    virtual QVariant readGlobalValue(const QString &key, const QVariant &defaultValue = QVariant()) const;
    template<typename T> inline
    T readGlobalValue(const QString &key, const QVariant &defaultValue = QVariant()) const
    { return readGlobalValue(key, defaultValue).value<T>(); }
    virtual void writeGlobalValue(const QString &key, const QVariant &value) const;

protected:
    virtual void saveStatus() const;
    virtual void restoreStatus();

private:
    Q_DISABLE_COPY(JStorableProxy)
    J_DECLARE_PRIVATE(JStorableProxy)
};

#endif  // STORABLEPROXY_H
