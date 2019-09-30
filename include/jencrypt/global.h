#ifndef JENCRYPT_GLOBAL_H
#define JENCRYPT_GLOBAL_H

#ifdef JENCRYPT_LIB
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#   ifdef JENCRYPT_BUILD
#       define JENCRYPT_EXPORT __declspec(dllexport)
#   else
#       define JENCRYPT_EXPORT __declspec(dllimport)
#   endif // !JENCRYPT_BUILD
#endif // _MSC_VER || ...
#endif // JENCRYPT_LIB

#ifndef JENCRYPT_EXPORT
#define JENCRYPT_EXPORT
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

#include <string>

namespace jencrypt {

typedef unsigned char	byte;
typedef unsigned int	uint32;

} // end of namespace jencrypt

#endif // JENCRYPT_GLOBAL_H
