QT += gui

TEMPLATE = lib
DEFINES += OPENCV_FORMAT_CONVERT_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    opencv_format_convert.cpp

HEADERS += \
    opencv_format_convert_global.h \
    opencv_format_convert.h

LIB_NAME = opencv_format_convert
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
include($${PRI_OPENCV_FORMAT_CONVERT})

