QT += quick
QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        work.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

HEADERS += \
    work.h

APP_NAME = random_text_stream
PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)
include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))
include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))

