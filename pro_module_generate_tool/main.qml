import QtQuick 2.15
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.0
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Qt pro module generate tool")

    signal startGen(string root_path_url, string module_file_url)

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 1

            RowLayout {
                anchors.fill: parent
                spacing: 10

                TextField {
                    id: _module_url
                    Layout.fillWidth: true
                }

                Button {
                    text: "sub pro file"
                    onClicked: {
                        _file_dlg.open()
                    }
                }
            }
        }
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 1

            RowLayout {
                anchors.fill: parent
                spacing: 10

                TextField {
                    id: _root_url
                    Layout.fillWidth: true
                }

                Button {
                    text: "root pro path"
                    onClicked: {
                        _path_dlg.open()
                    }
                }
            }
        }
        Item {
            Layout.fillWidth: true
            Layout.preferredHeight: 1

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "gen"
                onClicked: {
                    startGen(_root_url.text, _module_url.text)
                }
            }
        }
    }

    FileDialog {
        id: _file_dlg
        acceptLabel: "Select"
        title: "Sub Module .pro"
        onAccepted: {
            _module_url.text = file
        }
    }

    FileDialog {
        id: _path_dlg
        acceptLabel: "Select"
        title: "Root Path"
        onAccepted: {
            _root_url.text = folder
        }
    }
}
