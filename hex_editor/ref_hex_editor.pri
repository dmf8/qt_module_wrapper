if (!contains(DEFINES, INC_PRI_HEX_EDITOR)) {
    DEFINES += INC_PRI_HEX_EDITOR
    INCLUDEPATH += $${PWD}

    if (!contains(DEFINES, HEX_EDITOR_LIBRARY)) {
        _LIB_NAME_HEX_EDITOR = hex_editor

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_HEX_EDITOR}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_HEX_EDITOR}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_HEX_EDITOR}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_HEX_EDITOR}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_HEX_EDITOR}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_HEX_EDITOR}
                }
            }
        }
    }
}