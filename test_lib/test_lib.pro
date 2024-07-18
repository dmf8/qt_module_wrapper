QT -= gui

TEMPLATE = lib
DEFINES += TEST_LIB_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    test_lib.cpp

HEADERS += \
    test_lib_global.h \
    test_lib.h

