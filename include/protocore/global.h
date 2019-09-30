#ifndef PROTOCORE_GLOBAL_H
#define PROTOCORE_GLOBAL_H

#include "config.h"

////////////////////////////////

#include <string>
#include <vector>
#include <functional>
#include <stdint.h>
#include <assert.h>
#ifdef __unix__
#if __cplusplus >= 201103L
#include <exception>                // std::exception
#include <typeinfo>                 // std::type_info in get_deleter
#include <iosfwd>                   // std::basic_ostream
#ifndef __llvm__
#include <ext/atomicity.h>
#include <ext/concurrence.h>
#include <bits/functexcept.h>
#include <bits/stl_function.h>      // std::less
#include <bits/uses_allocator.h>
#include <bits/unique_ptr.h>
#include <bits/shared_ptr.h>
#endif
#include <type_traits>
#include <functional>
//#include <debug/debug.h>
#if defined(_GLIBCXX_USE_DEPRECATED)

#if defined(__LINUX)
#include <backward/auto_ptr.h>
#else
//#include <backward/auto_ptr.h>
#include <memory>
#endif

#endif
#else
#include <backward/auto_ptr.h>
#endif
typedef float float_t;
typedef double double_t;
#endif

#if defined(__APPLE__)
typedef float float_t;
typedef double double_t;
#endif

#include "./3rdpart/jsoncpp/json_tool.h"

#ifndef HAVE_NO_TINYXML
#include "./3rdpart/tinyxml/tinyxml.h"
#else
class TiXmlElement;
#endif

#if defined(__ANDROID__)
struct _JNIEnv;
typedef _JNIEnv JNIEnv;
#endif


/*  */
#if !defined(WIN32) && !defined(_countof)
template < typename T, size_t N >
size_t _countof( T ( & )[ N ] ) { return std::extent< T[ N ] >::value; }
#endif

/* These two macros makes it possible to turn the builtin line expander into a
 * string literal. */
#ifndef J_STRINGIFY2
#define J_STRINGIFY2(x) #x
#endif

#ifndef J_STRINGIFY
#define J_STRINGIFY(x) J_STRINGIFY2(x)
#endif

/* base64 - min - 22 */
#ifndef J_GUID_MIN_SIZE
#define J_GUID_MIN_SIZE 22
#endif

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

////////////////////////////////

#ifndef J_DEF_TYPE
#define J_DEF_TYPE

#ifdef _WIN32
#ifndef J_INT64_C
#define J_INT64_C(c) c ## i64
#endif
#ifndef J_UINT64_C
#define J_UINT64_C(c) c ## ui64
#endif
#else
#ifdef __cplusplus
#ifndef J_INT64_C
#define J_INT64_C(c) static_cast<long long>(c ## LL)
#endif
#ifndef J_UINT64_C
#define J_UINT64_C(c) static_cast<unsigned long long>(c ## ULL)
#endif
#else
#ifndef J_INT64_C
#define J_INT64_C(c) ((long long)(c ## LL))
#endif
#ifndef J_UINT64_C
#define J_UINT64_C(c) ((unsigned long long)(c ## ULL))
#endif
#endif
#endif

typedef float float32_t;
typedef double float64_t;

#endif // J_DEF_TYPE

#ifdef _WIN32
#if _MSC_VER >= 1600
#ifndef J_SPRINTF
#define J_SPRINTF sprintf_s
#endif
#else
#ifndef J_SPRINTF
#define J_SPRINTF sprintf
#endif
#endif
#else
#ifndef J_SPRINTF
#define J_SPRINTF sprintf
#endif
#endif

namespace J {

//
template<typename T>
struct disable_compare_t : public std::binary_function<T, T, bool>
{ bool operator ()(T, T) { return true; } };

//
typedef std::function<void(const std::string &msg, const std::string &type)> printf_callback;

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

//
#ifndef J_LIMIT_METHODS
#define J_LIMIT_METHODS
template <typename T>
inline const T &jMin(const T &a, const T &b) { return (a < b) ? a : b; }
template <typename T>
inline const T &jMax(const T &a, const T &b) { return (a < b) ? b : a; }
template <typename T>
inline const T &jBound(const T &min, const T &val, const T &max)
{ return jMax(min, jMin(max, val)); }
#endif
//
std::string PROTOCORE_EXPORT appDirPath();
//
#ifndef J_FUNC_STRING_CONVERT
#define J_FUNC_STRING_CONVERT
std::wstring PROTOCORE_EXPORT ansi2Unicode(const std::string& sAnsi);
std::string PROTOCORE_EXPORT unicode2Ansi(const std::wstring &sUnicode);
std::wstring PROTOCORE_EXPORT utf82Unicode(const std::string &sUtf8);
std::string PROTOCORE_EXPORT unicode2Utf8(const std::wstring& sUnicode);
std::string PROTOCORE_EXPORT utf82Ansi(const std::string &sUtf8);
std::string PROTOCORE_EXPORT ansi2Utf8(const std::string &sAnsi);
#endif  // J_FUNC_STRING_CONVERT
//
bool PROTOCORE_EXPORT startsWith(const std::string &str, const std::string &header,
                                 bool caseSensitive = true);
bool PROTOCORE_EXPORT endsWith(const std::string &str, const std::string &tail,
                               bool caseSensitive = true);
int PROTOCORE_EXPORT atoi(const std::string &str, int radix = 10);
unsigned int PROTOCORE_EXPORT atou(const std::string &str, int radix = 10);
uint64_t PROTOCORE_EXPORT strtou64(const std::string &str, int radix = 10);
uint64_t PROTOCORE_EXPORT atou64(const std::string &str);
std::string PROTOCORE_EXPORT itoa(int value, bool hex = false, int field = -1);
std::string PROTOCORE_EXPORT utoa(unsigned int value, bool hex = false, int field = -1);
std::string PROTOCORE_EXPORT u64toa(uint64_t value, bool hex = false, int field = -1);
std::string PROTOCORE_EXPORT u64tostr(uint64_t value, int radix = 10);
double PROTOCORE_EXPORT atod(const std::string &str);
std::string PROTOCORE_EXPORT dtoa(double value);

void PROTOCORE_EXPORT tolower(std::string &str);
void PROTOCORE_EXPORT toupper(std::string &str);
std::string PROTOCORE_EXPORT tolowered(const std::string &str);
std::string PROTOCORE_EXPORT touppered(const std::string &str);
std::string PROTOCORE_EXPORT stringSection(const char *ch, char sep, int start = 0, int end = -1);
std::string PROTOCORE_EXPORT stringSection(const std::string &str, char sep, int start = 0, int end = -1);
std::string PROTOCORE_EXPORT stringSection(const char *ch, const std::string &sep,
                                           int start = 0, int end = -1);
std::string PROTOCORE_EXPORT stringSection(const std::string &str, const std::string &sep,
                                           int start = 0, int end = -1);
void PROTOCORE_EXPORT splitString(const std::string &str, const std::string &delim,
                                  std::vector<std::string> &ret, bool keepEmptyParts = false);
std::string PROTOCORE_EXPORT trimString(const std::string &str);
std::string PROTOCORE_EXPORT &replaceString(std::string &str, const std::string &old_str,
                                            const std::string &new_str);
int PROTOCORE_EXPORT createPath(const std::string &path);
bool PROTOCORE_EXPORT pathExists(const std::string &path);
std::string PROTOCORE_EXPORT pathOfFile(const std::string &filePath);

int PROTOCORE_EXPORT asciiCountOfSize(int format, int size);
int PROTOCORE_EXPORT octSizeOfHexSize(int hexSize);

#if defined(__ANDROID__)
bool PROTOCORE_EXPORT initialize(JNIEnv *env, printf_callback callback = nullptr);
#else
bool PROTOCORE_EXPORT initialize(printf_callback callback = nullptr);
#endif
void PROTOCORE_EXPORT uninitialize();

std::string PROTOCORE_EXPORT base64_encode(const char *data, size_t size);
std::string PROTOCORE_EXPORT base64_decode(const std::string &str);

void PROTOCORE_EXPORT createUuidEx(std::string &uuid, bool base64 = true);
std::string PROTOCORE_EXPORT createUuid(bool base64 = true);

void PROTOCORE_EXPORT set_printf_callback(printf_callback callback);
void PROTOCORE_EXPORT printf_debug(const std::string &msg, const std::string &type = std::string());

// class Serializable

class Value;

class PROTOCORE_EXPORT Serializable
{
public:
    Serializable();
    virtual ~Serializable();
    virtual void beginSerial() const;
    virtual void endSerial() const;
    virtual Value save(const Value &creator) const = 0;
    virtual bool restore(const Value &value, int deep = -1) = 0;

    Serializable(const Serializable &other);
    Serializable &operator =(const Serializable &other);
};

// endian convert

typedef union __UnionFloat32
{
    uint32_t u32;
    float f32;
} UnionFloat32;

typedef union __UnionFloat64
{
    uint64_t u64;
    double f64;
} UnionFloat64;

template <typename T16>
inline T16 endian_swapi16(const T16 &v)
{
    assert(sizeof(T16) == 2);
    return ((v & 0x00ff) << 8) | ((v >> 8) & 0x00ff);
}

template <typename T16>
inline T16 endian_swapi16p(const char *data)
{
    assert(data != nullptr);
    return endian_swapi16(*reinterpret_cast<const T16*>(data));
}

template <typename T32>
inline T32 endian_swapi32(const T32 &v)
{
    assert(sizeof(T32) == 4);
    return (((v >> 24) & 0x000000ff)
            | (((v & 0x00ff0000) >> 8) & 0x0000ff00)
            | ((v & 0x0000ff00) << 8)
            | (v << 24));
}

template <typename T32>
inline T32 endian_swapi32p(const char *data)
{
    assert(data != nullptr);
    return endian_swapi32(*reinterpret_cast<const T32*>(data));
}

template <typename T64>
inline T64 endian_swapi64(const T64 &v)
{
    assert(sizeof(T64) == 8);
    return (((v >> 56) & 0x00000000000000ff)
            | (((v & 0x00ff000000000000) >> 40) & 0x000000000000ff00)
            | (((v & 0x0000ff0000000000) >> 24) & 0x0000000000ff0000)
            | (((v & 0x000000ff00000000) >> 8) & 0x00000000ff000000)
            | ((v & 0x00000000ff000000) << 8)
            | ((v & 0x0000000000ff0000) << 24)
            | ((v & 0x000000000000ff00) << 40)
            | (v << 56));
}

template <typename T64>
inline T64 endian_swapi64p(const char *data)
{
    assert(data != nullptr);
    return endian_swapi64(*reinterpret_cast<const T64*>(data));
}

inline float endian_swapf32(float v)
{
    assert(sizeof(float) == 4);
    UnionFloat32 uf;
    uf.f32 = v;
    uf.u32 = endian_swapi32(uf.u32);
    return uf.f32;
}

inline float endian_swapf32(uint32_t v)
{
    assert(sizeof(float) == 4);
    UnionFloat32 uf;
    uf.u32 = v;
    uf.u32 = endian_swapi32(uf.u32);
    return uf.f32;
}

inline float endian_swapf32p(const char *data)
{
    assert(data != nullptr);
    return endian_swapf32(*reinterpret_cast<const uint32_t*>(data));
}

inline double endian_swapf64(double v)
{
    assert(sizeof(double) == 8);
    UnionFloat64 uf;
    uf.f64 = v;
    uf.u64 = endian_swapi64(uf.u64);
    return uf.f64;
}

inline double endian_swapf64(uint64_t v)
{
    assert(sizeof(double) == 8);
    UnionFloat64 uf;
    uf.u64 = v;
    uf.u64 = endian_swapi64(uf.u64);
    return uf.f64;
}

inline double endian_swapf64p(const char *data)
{
    assert(data != nullptr);
    return endian_swapf64(*reinterpret_cast<const uint64_t*>(data));
}

template <typename T>
inline T endian_swap(const T &v)
{
    T r;
    const int size = sizeof(v);
    const unsigned char *cvi = reinterpret_cast<const unsigned char *>(&v);
    unsigned char *cri = reinterpret_cast<unsigned char *>(&r);

    cri = cri + size - 1;

    for (int i = 0; i < size; ++i) {
        *cri = *cvi;
        ++cvi;
        --cri;
    }

    return r;
}

} // end of namespace J

#endif // PROTOCORE_GLOBAL_H
