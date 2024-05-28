QT -= gui

TEMPLATE = lib
DEFINES += TEXT_WRITE_SEEKER_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    text_write_seeker.cpp

HEADERS += \
    text_write_seeker_global.h \
    text_write_seeker.h


