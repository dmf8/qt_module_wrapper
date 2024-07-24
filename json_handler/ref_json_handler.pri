if (!contains(DEFINES, INC_PRI_JSON_HANDLER)) {
    DEFINES += INC_PRI_JSON_HANDLER
    INCLUDEPATH += $${PWD}

    if (!contains(DEFINES, JSON_HANDLER_LIBRARY)) {
        _LIB_NAME_JSON_HANDLER = json_handler

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_JSON_HANDLER}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_JSON_HANDLER}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_JSON_HANDLER}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_JSON_HANDLER}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_JSON_HANDLER}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_JSON_HANDLER}
                }
            }
        }
    }
}




