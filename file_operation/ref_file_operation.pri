if (!contains(DEFINES, INC_PRI_FILE_OPERATION)) {
    DEFINES += INC_PRI_FILE_OPERATION
    INCLUDEPATH += $${PWD}

    if (!contains(DEFINES, FILE_OPERATION_LIBRARY)) {
        _LIB_NAME_FILE_OPERATION = file_operation

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_FILE_OPERATION}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_FILE_OPERATION}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_FILE_OPERATION}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_FILE_OPERATION}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_FILE_OPERATION}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_FILE_OPERATION}
                }
            }
        }
    }
}