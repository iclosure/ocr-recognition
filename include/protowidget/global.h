#ifndef PROTOWIDGET_GLOBAL_H
#define PROTOWIDGET_GLOBAL_H

#include "protocore/global.h"
#include "jwt/global.h"

#ifdef PROTOWIDGET_LIB
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#   ifdef PROTOWIDGET_BUILD
#       define PROTOWIDGET_EXPORT __declspec(dllexport)
#   else
#       define PROTOWIDGET_EXPORT __declspec(dllimport)
#   endif // !PROTOWIDGET_BUILD
#endif // _MSC_VER || ...
#endif // PROTOWIDGET_LIB

#ifndef PROTOWIDGET_EXPORT
#define PROTOWIDGET_EXPORT
#endif

////////////////////////////////

#ifndef J_DECLARE_SINGLE_INSTANCE
#define J_DECLARE_SINGLE_INSTANCE(Class) \
    public: \
    static Class *instance(); \
    static void releaseInstance(); \
    private: \
    static Class *_instance;
#endif

#ifndef J_IMPLEMENT_SINGLE_INSTANCE
#define J_IMPLEMENT_SINGLE_INSTANCE(Class, GlobalClass) \
    \
    static void __ ## Class ## _releaseInstance() { \
    Class::releaseInstance(); \
    } \
    Class *Class::_instance = nullptr; \
    \
    Class *Class::instance() { \
    if (Class::_instance == nullptr) { \
    Class::_instance = new Class; \
    } \
    if (QLatin1String(QT_STRINGIFY(Class)) != #GlobalClass) { \
    GlobalClass::instance()->registerSingletonRelease(__ ## Class ## _releaseInstance); \
    } \
    return Class::_instance; \
    } \
    \
    void Class::releaseInstance() { \
    if (Class::_instance != nullptr) { \
    delete Class::_instance; \
    Class::_instance = nullptr; \
    } \
    }
#endif

#ifndef J_SINGLE_RELEASE_CALLBACK
#define J_SINGLE_RELEASE_CALLBACK
typedef void(*SingletonReleaseCallback)();
#endif

#ifndef J_NO_QT

#ifndef J_TYPEDEF_QT_SHAREDPTR
#define J_TYPEDEF_QT_SHAREDPTR(_class_) \
    class _class_; \
    typedef QSharedPointer<_class_> _class_ ## Ptr; \
    typedef QList<_class_ ## Ptr> _class_ ## PtrArray;
#endif

#ifndef J_VARIANT_FROM_VOID
#define J_VARIANT_FROM_VOID
#include <QVariant>
template<typename T> inline
T *jVariantFromVoid(const QVariant &value)
{ return reinterpret_cast<T *>(value.value<void *>()); }
#endif

#endif

////////////////////////////////

#include <memory>

class QFileDevice;

#ifndef J_NO_QT
#include <qglobal.h>
#include <QStandardItem>
#include <QObject>
#include <QEvent>
#endif

namespace J {

#ifndef J_DELETE_QOBJECT
#define J_DELETE_QOBJECT

inline void jdelete_qobject(QObject *object)
{
    delete object;
}

#endif // J_DELETE_QOBJECT

enum TreeItemType {
#ifndef J_NO_QT
    TreeItemTypeUserRole = QStandardItem::UserType + 1,
#else
    TreeItemTypeUserRole = 1000 + 1,
#endif
    TreeItemTypeRoot,
    TreeItemTypeVehicle,
    TreeItemTypeSystem,
    TreeItemTypeTable,
    TreeItemTypeDataItem,
    TreeItemTypeItemTable,
    TreeItemTypeItemArrayItem,
    TreeItemTypeItemBit
};

enum TreeItemDataRole {
#ifndef J_NO_QT
    TreeItemUserRole = Qt::UserRole + 1,
#else
    TreeItemUserRole = 0x0100 + 1,
#endif
    TreeItemIdRole,
    TreeItemDomainRole,
    TreeItemPathRole,
    TreeItemNewRole,
    TreeItemMarkRole,
    TreeChannelIdRole,
    TreeDataRttiRole,
    TreeBoundRole,
    TreeArrayIndexRole,
    TreeBitOffsetRole,
    TreeFilePathRole,
    TreeHasTimeFormatRole,
    TreeHeaderSizeRole,
    TreeLoadStatusRole
};

#ifndef J_ENUM_CUSTOM_EVENT
#define J_ENUM_CUSTOM_EVENT

enum CustomEvent {
    Event_Callback = QEvent::User + 100,
    Event_StateMachine,
    Event_SetProperty,
    Event_ProtocolFeedback,

    Event_User = QEvent::User + 500
};

class PROTOWIDGET_EXPORT JCallbackEvent : public QEvent
{
public:
    typedef std::function<void(const QVariantList &)> Caller;

    explicit JCallbackEvent(Caller callback, const QVariantList &arguments)
        : QEvent(static_cast<Type>(Event_Callback))
        , callback_(callback)
        , args_(arguments)
    {

    }

    bool isValid() const { return (callback_ != nullptr); }

    void execute()
    {
        if (callback_) {
            Caller callback = callback_;
            callback_ = nullptr;
            callback(args_);
        }
    }

private:
    Caller callback_;
    QVariantList args_;
};

#endif  // J_ENUM_CUSTOM_EVENT

#ifndef J_NO_QT

template<typename T>
inline ::std::shared_ptr<T> handlescope_cast(const QVariant &variant)
{
    JHandleScope<T> *handleScope = jVariantFromVoid<JHandleScope<T> >(variant);
    if (handleScope) {
        return handleScope->ptr;
    }
    return nullptr;
}

template<typename T>
inline ::std::weak_ptr<T> weakscope_cast(const QVariant &variant)
{
    JWeakScope<T> *weakScope = jVariantFromVoid<JWeakScope<T> >(variant);
    if (weakScope) {
        return weakScope->ptr;
    }
    return nullptr;
}
#endif
//
class Item;
typedef ::std::shared_ptr<Item> ItemPtr;
class Table;
typedef ::std::shared_ptr<Table> TablePtr;

bool PROTOWIDGET_EXPORT checkData(const TablePtr &table, int fileHeaderSize,
                                  QFileDevice *source, QFileDevice *target);

} // end of namespace J

// class WidgetCore

class WidgetCorePrivate;

#ifndef J_NO_QT

class PROTOWIDGET_EXPORT WidgetCore : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void(const QVariantList &/*args*/)> AsyncCaller;
    typedef std::function<void(const QVariantList &/*args*/)> DelayCaller;

    bool init();

    void registerSingletonRelease(SingletonReleaseCallback callback);

    // {{ for protocore/core
    static QStringList protoItemTypes();
    static QMap<int, QString> protoItemMapTypes();
    static QString typeString(const J::ItemPtr &item);
    static QString counterTypeString(int counterType);
    static QString checkTypeString(int checkType);
    static QString numericTypeString(int numericType);
    static QString arrayTypeString(int arrayType);
    static QString frameCodeTypeString(int frameCodeType);
    static QString dateTimeTypeString(int dateTimeType);
    // }} for protocore/core

    static QString prettyValue(double value, bool isFloat = false);

    bool setLocaleName(const QString &localeName);

    static QString configFile();
    static QByteArray &replaceConfig(QByteArray &content, bool reverse);
    static QString &replaceConfig(QString &content, bool reverse);

    static void cleanTempFiles();
    static void clearTempSettings();

    void startAwait();
    void stopAwait();
    void asyncCall(AsyncCaller callback, const QVariantList &args = QVariantList());
    void delayCall(DelayCaller callback, const QVariantList &args = QVariantList(), qint64 msecs = 10000);
    void cancelDelayCall();

Q_SIGNALS:

public Q_SLOTS:

protected:
    void customEvent(QEvent *event) override;

private:
    explicit WidgetCore(QObject *parent = nullptr);
    ~WidgetCore() J_OVERRIDE;

private:
    Q_DISABLE_COPY(WidgetCore)
    J_DECLARE_PRIVATE(WidgetCore)
    J_DECLARE_SINGLE_INSTANCE(WidgetCore)
};

#endif

#endif // PROTOWIDGET_GLOBAL_H
