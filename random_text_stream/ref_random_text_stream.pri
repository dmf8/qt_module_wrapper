if (!contains(DEFINES, INC_PRI_RANDOM_TEXT_STREAM)) {
    DEFINES += INC_PRI_RANDOM_TEXT_STREAM
    INCLUDEPATH += $${PWD}

    if (!contains(DEFINES, RANDOM_TEXT_STREAM_LIBRARY)) {
        _LIB_NAME_RANDOM_TEXT_STREAM = random_text_stream

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_RANDOM_TEXT_STREAM}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_RANDOM_TEXT_STREAM}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_RANDOM_TEXT_STREAM}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_RANDOM_TEXT_STREAM}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_RANDOM_TEXT_STREAM}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_RANDOM_TEXT_STREAM}
                }
            }
        }
    }
}
