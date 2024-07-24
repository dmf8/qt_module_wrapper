QT -= gui

TEMPLATE = lib
DEFINES += DATA_HANDLER_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data_handler.cpp \
    line_intersection.cpp \
    peak_detect.cpp \
    statistics.cpp

HEADERS += \
    data_handler_global.h \
    data_handler.h \
    line_intersection.h \
    peak_detect.h \
    statistics.h

LIB_NAME = data_handler
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
include($${PRI_DATA_HANDLER})
