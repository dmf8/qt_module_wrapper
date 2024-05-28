#ifndef RANDOM_TEXT_STREAM_GLOBAL_H
#define RANDOM_TEXT_STREAM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RANDOM_TEXT_STREAM_LIBRARY)
#  define RANDOM_TEXT_STREAM_EXPORT Q_DECL_EXPORT
#else
#  define RANDOM_TEXT_STREAM_EXPORT Q_DECL_IMPORT
#endif

#endif // RANDOM_TEXT_STREAM_GLOBAL_H
