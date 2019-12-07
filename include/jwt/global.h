#ifndef JWT_GLOBAL_H
#define JWT_GLOBAL_H

#ifndef J_NO_QT

#include <qglobal.h>
#include <QString>
#include <QFontMetrics>
#include <QEvent>

#endif  // J_NO_QT

// JWT_VERSION is (major << 16) + (minor << 8) + patch.

#define JWT_VERSION       0x010000
#define JWT_VERSION_STR   "1.0.0"

#ifdef JWT_LIB
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#   ifdef JWT_BUILD
#       define JWT_EXPORT  Q_DECL_EXPORT
#   else
#       define JWT_EXPORT  Q_DECL_IMPORT
#   endif // !JWT_BUILD
#endif // _MSC_VER || ...
#endif // JWT_LIB

#ifndef JWT_EXPORT
#define JWT_EXPORT
#endif

////////////////////////////////

#ifdef __unix__
#if __cplusplus >= 201103L
#  include <exception>              // std::exception
#  include <typeinfo>               // std::type_info in get_deleter
#  include <iosfwd>                 // std::basic_ostream
#  include <ext/atomicity.h>
#  include <ext/concurrence.h>
#  include <bits/functexcept.h>
#  include <bits/stl_function.h>  // std::less
#  include <bits/uses_allocator.h>
#  include <type_traits>
#  include <functional>
#  include <debug/debug.h>
#  include <bits/unique_ptr.h>
#  include <bits/shared_ptr.h>
#  if _GLIBCXX_USE_DEPRECATED
#    include <backward/auto_ptr.h>
#  endif
#else
#  include <backward/auto_ptr.h>
#endif
typedef float float_t;
typedef double double_t;
#endif

#if defined(__apple__)
typedef float float_t;
typedef double double_t;
#endif

/* These two macros makes it possible to turn the builtin line expander into a
 * string literal. */
#ifndef J_STRINGIFY2
#define J_STRINGIFY2(x) #x
#endif

#ifndef J_STRINGIFY
#define J_STRINGIFY(x) J_STRINGIFY2(x)
#endif

/* */
#ifdef _MSC_VER
#if _MSC_VER > 1600
#define J_OVERRIDE override
#else
#define J_OVERRIDE
#endif
#else
#define J_OVERRIDE override
#endif

// for shared_ptr
#include <memory>
#ifndef shared_cast
#define shared_cast std::dynamic_pointer_cast
#endif

#ifndef J_DISABLE_COPY
#define J_DISABLE_COPY(Class) \
    Class(const Class &);\
    Class &operator=(const Class &);
#endif

// - private pointer
#ifndef J_DECLARE_PRIVATE
#define J_DECLARE_PRIVATE(Class) \
    Class##Private *d_ptr_; \
    inline Class##Private* d_func() { return d_ptr_; } \
    inline const Class##Private* d_func() const { return d_ptr_; } \
    friend class Class##Private;
#endif

#ifndef J_DECLARE_PUBLIC
#define J_DECLARE_PUBLIC(Class) \
    Class *q_ptr_; \
    inline Class* q_func() { return q_ptr_; } \
    inline const Class* q_func() const { return q_ptr_; } \
    friend class Class;
#endif

#ifndef J_DPTR
#define J_DPTR d_ptr_
#endif

#ifndef J_QPTR
#define J_QPTR q_ptr_
#endif

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

/* */
#ifdef _MSC_VER
#if _MSC_VER > 1600
#define J_OVERRIDE override
#else
#define J_OVERRIDE
#endif
#else
#define J_OVERRIDE override
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

// handlescope
#ifndef J_HANDLE_SCOPE
#define J_HANDLE_SCOPE
template<typename T> struct JHandleScope { std::shared_ptr<T> ptr; };
#endif

// weakscope
#ifndef J_WEAK_SCOPE
#define J_WEAK_SCOPE
template<typename T> struct JWeakScope { std::weak_ptr<T> ptr; };
#endif

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

#endif  // J_NO_QT

namespace jwt {

static const double jDoubleEpsion = 1E-6;
static const float jFDoubleEpsion = 1E-6f;

// ==
inline bool jEqual(double a, double b)
{ return (a - b > -jDoubleEpsion || a - b < jDoubleEpsion) ? true : false; }
inline bool fEqual(float a, float b)
{ return (a - b > -jFDoubleEpsion || a - b < jFDoubleEpsion) ? true : false; }

// >
inline bool fGreater(double a, double b)
{ return (a - b > jDoubleEpsion) ? true : false; }
inline bool fGreater(float a, float b)
{ return (a - b > jFDoubleEpsion) ? true : false; }

// <
inline bool fLess(double a, double b)
{ return (a - b < -jDoubleEpsion) ? true : false; }
inline bool fLess(float a, float b)
{ return (a - b < -jFDoubleEpsion) ? true : false; }

// >=
inline bool fGreaterOrEqual(double a, double b)
{ return ((a - b > jDoubleEpsion) ||  (a - b >= -jDoubleEpsion && a - b <= jDoubleEpsion)) ? true : false; }
inline bool fGreaterOrEqual(float a, float b)
{ return ((a - b > jFDoubleEpsion) ||  (a - b >= -jFDoubleEpsion && a - b <= jFDoubleEpsion)) ? true : false; }

// <=
inline bool fLessOrEqual(double a, double b)
{ return ((a - b < -jDoubleEpsion) || (a - b >= -jDoubleEpsion && a - b <= jDoubleEpsion)) ? true : false; }
inline bool fLessOrEqual(float a, float b)
{ return ((a - b < -jFDoubleEpsion) || (a - b >= -jFDoubleEpsion && a - b <= jFDoubleEpsion)) ? true : false; }

#ifndef J_NO_QT

#ifndef J_DELETE_QOBJECT
#define J_DELETE_QOBJECT

inline void jdelete_qobject(QObject *object)
{
    delete object;
}

#endif // J_DELETE_QOBJECT

#ifndef J_ENUM_CUSTOM_EVENT
#define J_ENUM_CUSTOM_EVENT

enum CustomEvent {
    Event_Callback = QEvent::User + 100,
    Event_StateMachine,
    Event_SetProperty,
    Event_ProtocolFeedback,

    Event_User = QEvent::User + 500
};

class JWT_EXPORT JCallbackEvent : public QEvent
{
public:
    typedef std::function<void(const QVariantList &)> Caller;

    explicit JCallbackEvent(Caller callback, const QVariantList &arguments);
    ~JCallbackEvent() J_OVERRIDE;

    bool isValid() const;
    void execute();

private:
    Q_DISABLE_COPY(JCallbackEvent)
    Caller callback_;
    QVariantList args_;
};

#endif  // J_ENUM_CUSTOM_EVENT

#endif  // J_NO_QT

}   // end of namespace jwt

// - class Jwt -

#include <QObject>
#include <QVariant>

class JwtPrivate;
class QTranslator;
class QLocale;

class JWT_EXPORT Jwt : public QObject
{
    Q_OBJECT
public:
    enum TimeSpec {
        TimeSpec_HourMin,
        TimeSpec_MinuteMin,
        TimeSpec_SecondMin,
        TimeSpec_MSecondMin
    };
    Q_ENUM(TimeSpec)

    typedef std::function<void(const QVariantList &/*args*/)> AsyncCaller;
    typedef std::function<void(const QVariantList &/*args*/)> DelayCaller;

    void init();

    bool setLocaleName(const QString &localeName = QString());

    void registerSingletonRelease(SingletonReleaseCallback callback);

    static int fontWidth(const QString &text, const QFontMetrics &fontMetrics);
    static qreal fontWidth(const QString &text, const QFontMetricsF &fontMetrics);

    static void saveWidgetState(QWidget *widget, const QString prefix = QString());
    static bool restoreWidgetState(QWidget *widget, const QString prefix = QString(),
                                   const QVariant &defaultValue = QVariant());
    static QString settingsGroupPrefix(const QString prefix = QString());

    static QByteArray &replaceConfig(QByteArray &content, bool reverse);
    static QString &replaceConfig(QString &content, bool reverse);

    static QVariant readStore(const QString &key, const QVariant &defaultValue = QVariant());
    template<typename T> inline
    static T readStore(const QString &key, const QVariant &defaultValue = QVariant())
    { return readStore(key, defaultValue).value<T>(); }
    static bool writeStore(const QString &key, const QVariant &value);
    static bool containsStore(const QString &key);
    static void clearStore(const QString &key = QString());

    static void sortVersions(QStringList &versions);
    static int compareVersion(const QString &version1, const QString &version2);

    static void cleanTempFiles();
    static void clearTempSettings();

    void startAwait();
    void stopAwait();
    void asyncCall(AsyncCaller callback, const QVariantList &args = QVariantList());
    void delayCall(DelayCaller callback, const QVariantList &args = QVariantList(),
                   qint64 msecs = 10000);
    void cancelDelayCall();

    static QString timeToStringByMsec(qint64 msecs, Jwt::TimeSpec spec = TimeSpec_MSecondMin);

protected:
    void customEvent(QEvent *event) override;

private:
    explicit Jwt(QObject *parent = nullptr);
    ~Jwt() J_OVERRIDE;

private:
    Q_DISABLE_COPY(Jwt)
    J_DECLARE_PRIVATE(Jwt)
    J_DECLARE_SINGLE_INSTANCE(Jwt)
};

// - class JAutoCursor -

class JWT_EXPORT JAutoCursor
{
public:
    explicit JAutoCursor(Qt::CursorShape shape);
    ~JAutoCursor();

    void activate(Qt::CursorShape shape = Qt::BusyCursor);
    void restore();

private:
    Q_DISABLE_COPY(JAutoCursor)
};

#endif // JWT_GLOBAL_H
