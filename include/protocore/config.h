#ifndef PROTOCORE_CONFIG_H
#define PROTOCORE_CONFIG_H

/* #undef HAVE_NO_TINYXML */

/* #undef HAVE_NO_SQL */

/* #undef HAVE_NO_SOCI */

/* #undef HAVE_NO_SQLITE3 */

/* #undef HAVE_NO_CHANNEL_ARINC429 */

/* #undef HAVE_NO_CHANNEL_BLE */

/* #undef HAVE_NO_CHANNEL_SERIAL */

/* #undef HAVE_NO_CHANNEL_SOCKET */

#ifdef PROTOCORE_LIB
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#   ifndef HAVE_NO_TINYXML
#       ifndef TINYXML_DLL
#           define TINYXML_DLL
#       endif
#   endif
#   ifdef PROTOCORE_BUILD
#       define PROTOCORE_EXPORT __declspec(dllexport)
#       ifndef JSON_DLL_BUILD
#           define JSON_DLL_BUILD
#       endif
#       ifndef HAVE_NO_TINYXML
#           ifndef TINYXML_BUILD
#               define TINYXML_BUILD
#           endif
#       endif
#   else
#       define PROTOCORE_EXPORT __declspec(dllimport)
#       ifndef JSON_DLL
#           define JSON_DLL
#       endif
#   endif // !PROTOCORE_BUILD
#endif // _MSC_VER || ...
#endif // PROTOCORE_LIB

#ifndef PROTOCORE_EXPORT
#if defined(__APPLE__)
#define PROTOCORE_EXPORT __attribute__((visibility("default")))
#else
#define PROTOCORE_EXPORT
#endif
#endif

#endif  // PROTOCORE_CONFIG_H
