if (!contains(DEFINES, INC_PRI_OPENCV_FORMAT_CONVERT)) {
    DEFINES += INC_PRI_OPENCV_FORMAT_CONVERT
    INCLUDEPATH += $${PWD}
    include($${PRI_OPENCV_440})

    if (!contains(DEFINES, OPENCV_FORMAT_CONVERT_LIBRARY)) {
        _LIB_NAME_OPENCV_FORMAT_CONVERT = opencv_format_convert

        win32 {
            CONFIG(debug,debug|release){
                LIBS += -L$${DEBUG_PATH_WIN32} -l$${_LIB_NAME_OPENCV_FORMAT_CONVERT}d
            } else {
                LIBS += -L$${RELEASE_PATH_WIN32} -l$${_LIB_NAME_OPENCV_FORMAT_CONVERT}
            }
        }

        unix {
            CONFIG(debug,debug|release){
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_OPENCV_FORMAT_CONVERT}d
                } else {
                    LIBS += -L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_OPENCV_FORMAT_CONVERT}d
                }
            } else {
                contains(QT_ARCH, arm64) {
                    LIBS += -L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_OPENCV_FORMAT_CONVERT}
                } else {
                    LIBS += -L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_OPENCV_FORMAT_CONVERT}
                }
            }
        }
    }
}
