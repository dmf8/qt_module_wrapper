QT -= gui

TEMPLATE = lib
DEFINES += WAIT_FOR_RESULT_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    wait_direct_call.cpp \
    wait_for_result.cpp \
    wait_for_result2.cpp

HEADERS += \
    wait_direct_call.h \
    wait_for_result2.h \
    wait_for_result_global.h \
    wait_for_result.h


LIB_NAME = wait_for_result
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
include($${PRI_WAIT_FOR_RESULT})
