#ifndef JSON_HANDLER_GLOBAL_H
#define JSON_HANDLER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(JSON_HANDLER_LIBRARY)
#  define JSON_HANDLER_EXPORT Q_DECL_EXPORT
#else
#  define JSON_HANDLER_EXPORT Q_DECL_IMPORT
#endif

#endif // JSON_HANDLER_GLOBAL_H
