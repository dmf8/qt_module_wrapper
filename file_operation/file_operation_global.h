#ifndef FILE_OPERATION_GLOBAL_H
#define FILE_OPERATION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FILE_OPERATION_LIBRARY)
#  define FILE_OPERATION_EXPORT Q_DECL_EXPORT
#else
#  define FILE_OPERATION_EXPORT Q_DECL_IMPORT
#endif

#endif // FILE_OPERATION_GLOBAL_H