QT -= gui

TEMPLATE = lib
DEFINES += RANDOM_TEXT_STREAM_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    csv_editor.cpp \
    random_text_stream.cpp

HEADERS += \
    csv_editor.h \
    random_text_stream_global.h \
    random_text_stream.h

LIB_NAME = random_text_stream
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
include($${PRI_RANDOM_TEXT_STREAM})
