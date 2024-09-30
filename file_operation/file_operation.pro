QT -= gui

TEMPLATE = lib
DEFINES += FILE_OPERATION_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base_operation.cpp \
    file_folder_handler.cpp \
    file_operation.cpp \
    path_operation.cpp

HEADERS += \
    base_operation.h \
    file_folder_handler.h \
    file_operation_global.h \
    file_operation.h \
    path_operation.h \
    test_cases.h

LIB_NAME = file_operation
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
include($${PRI_FILE_OPERATION})
