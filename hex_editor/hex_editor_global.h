#ifndef HEX_EDITOR_GLOBAL_H
#define HEX_EDITOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HEX_EDITOR_LIBRARY)
#  define HEX_EDITOR_EXPORT Q_DECL_EXPORT
#else
#  define HEX_EDITOR_EXPORT Q_DECL_IMPORT
#endif

#endif // HEX_EDITOR_GLOBAL_H
