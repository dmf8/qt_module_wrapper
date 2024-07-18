#ifndef TEST_LIB_GLOBAL_H
#define TEST_LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TEST_LIB_LIBRARY)
#  define TEST_LIB_EXPORT Q_DECL_EXPORT
#else
#  define TEST_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // TEST_LIB_GLOBAL_H
