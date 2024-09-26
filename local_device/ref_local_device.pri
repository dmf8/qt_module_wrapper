if (!contains(DEFINES, INC_PRI_LOCAL_DEVICE)) {
    DEFINES += INC_PRI_LOCAL_DEVICE
    INCLUDEPATH += $${PWD}

    if (!contains(DEFINES, LOCAL_DEVICE_LIBRARY)) {
        _LIB_NAME_LOCAL_DEVICE = local_device

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_LOCAL_DEVICE}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_LOCAL_DEVICE}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_LOCAL_DEVICE}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_LOCAL_DEVICE}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_LOCAL_DEVICE}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_LOCAL_DEVICE}
                }
            }
        }
    }
}