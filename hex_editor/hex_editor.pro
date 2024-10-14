QT -= gui

TEMPLATE = lib
DEFINES += HEX_EDITOR_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hex_editor.cpp

HEADERS += \
    hex_editor_global.h \
    hex_editor.h

LIB_NAME = hex_editor
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
include($${PRI_HEX_EDITOR})
