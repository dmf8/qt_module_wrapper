QT -= gui

TEMPLATE = lib
DEFINES += LOCAL_DEVICE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    local_device.cpp

HEADERS += \
    local_device_global.h \
    local_device.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
LIB_NAME = local_device
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
include($${PRI_LOCAL_DEVICE})
