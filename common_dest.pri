contains(TEMPLATE, app) {
    DST_NAME = $$APP_NAME
}
contains(TEMPLATE, lib) {
    DST_NAME = $$LIB_NAME
}

DEBUG_PATH_WIN32 = $$absolute_path($${PROJECT_ROOT_PATH}/bin/Debug/)
RELEASE_PATH_WIN32 = $$absolute_path($${PROJECT_ROOT_PATH}/bin/Release/)
DEBUG_PATH_LINUX_X86 = $$DEBUG_PATH_WIN32
RELEASE_PATH_LINUX_X86 = $$RELEASE_PATH_WIN32
DEBUG_PATH_LINUX_ARM64 = $$absolute_path($${DEBUG_PATH_WIN32}/arm64/)
RELEASE_PATH_LINUX_ARM64 = $$absolute_path($${RELEASE_PATH_WIN32}/arm64/)

win32 {
    CONFIG(debug,debug|release){
        TARGET = $${DST_NAME}d
        DESTDIR = $$DEBUG_PATH_WIN32
    } else {
        TARGET = $${DST_NAME}
        DESTDIR = $$RELEASE_PATH_WIN32
    }
}

unix {
    CONFIG(debug,debug|release){
        TARGET = $${DST_NAME}d
        contains(QT_ARCH, arm64) {
            DESTDIR = $$DEBUG_PATH_LINUX_ARM64
        } else {
            DESTDIR = $$DEBUG_PATH_LINUX_X86
        }
    } else {
        TARGET = $${DST_NAME}
        contains(QT_ARCH, arm64) {
            DESTDIR = $$RELEASE_PATH_LINUX_ARM64
        } else {
            DESTDIR = $$RELEASE_PATH_LINUX_X86
        }
    }
}

