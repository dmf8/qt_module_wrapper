QT += gui

TEMPLATE = lib
DEFINES += V4L2_USB_CAMERA_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    camera_process.cpp \
    camera_step.cpp

HEADERS += \
    camera_global.h \
    camera.h \
    camera_process.h \
    camera_step.h

LIB_NAME = v4l2_usb_camera
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))
include($${PRI_V4L2_USB_CAMERA})
