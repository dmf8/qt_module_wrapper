if (!contains(DEFINES, INC_PRI_WAIT_FOR_RESULT)) {
    DEFINES += INC_PRI_WAIT_FOR_RESULT
    INCLUDEPATH += $${PWD}

    if (!contains(DEFINES, WAIT_FOR_RESULT_LIBRARY)) {
        _LIB_NAME_WAIT_FOR_RESULT = wait_for_result

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_WAIT_FOR_RESULT}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_WAIT_FOR_RESULT}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_WAIT_FOR_RESULT}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_WAIT_FOR_RESULT}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_WAIT_FOR_RESULT}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_WAIT_FOR_RESULT}
                }
            }
        }
    }
}