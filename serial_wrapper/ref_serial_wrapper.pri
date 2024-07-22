if (!contains(DEFINES, INC_PRI_SERIAL_WRAPPER)) {
    DEFINES += INC_PRI_SERIAL_WRAPPER
    INCLUDEPATH += $${PWD}

    if (!contains(DEFINES, SERIAL_WRAPPER_LIBRARY)) {
        _LIB_NAME_SERIAL_WRAPPER = serial_wrapper

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_SERIAL_WRAPPER}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_SERIAL_WRAPPER}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_SERIAL_WRAPPER}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_SERIAL_WRAPPER}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_SERIAL_WRAPPER}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_SERIAL_WRAPPER}
                }
            }
        }
    }
}