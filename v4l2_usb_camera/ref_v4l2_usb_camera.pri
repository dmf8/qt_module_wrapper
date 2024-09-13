if (!contains(DEFINES, INC_PRI_V4L2_USB_CAMERA)) {
    DEFINES += INC_PRI_V4L2_USB_CAMERA
    INCLUDEPATH += $${PWD}

    if (!contains(DEFINES, V4L2_USB_CAMERA_LIBRARY)) {
        _LIB_NAME_USB_CAMERA = v4l2_usb_camera

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_USB_CAMERA}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_USB_CAMERA}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_USB_CAMERA}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_USB_CAMERA}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_USB_CAMERA}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_USB_CAMERA}
                }
            }
        }
    }
}
