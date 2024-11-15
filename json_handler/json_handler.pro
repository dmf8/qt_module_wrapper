QT -= gui

TEMPLATE = lib
DEFINES += JSON_HANDLER_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    json_handler.cpp \
    json_object_index.cpp

HEADERS += \
    json_handler_global.h \
    json_handler.h \
    json_object_index.h

LIB_NAME = json_handler
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
# ref self
include($${PRI_JSON_HANDLER})
