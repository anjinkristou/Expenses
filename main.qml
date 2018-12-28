import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.4

Window {
    visible: true
    title: qsTr("Hello World")
    height: 600
    width: 400

    Material.theme: Material.Light
    Material.accent: Material.Blue

    Page {
        anchors.fill: parent
        header: ToolBar {
            RowLayout {
                anchors.fill: parent
                ToolButton {
                    onClicked: stackView.pop()
                    enabled: stackView.depth > 1
                    icon.source: "icon/back"
                }
                Label {
                    text: "Expenses"
                    elide: Label.ElideRight
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }
            }
        }

        StackView {
            id: stackView
            anchors.fill: parent
            initialItem: sheetList

            SheetPage {
                id: sheetList
                sheets: sheetCollection
                onSheetSelected : stackView.push(recordList)
            }

            RecordPage {
                id: recordList
                sheet: sheetList.selectedSheet
            }
        }
    }
}
