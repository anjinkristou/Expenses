import QtQuick 2.0
import QtQuick.Controls 2.12

Page {
    id: root

    property alias sheets : sheetList.sheets
    property alias selectedSheet: sheetList.selectedSheet
    signal sheetSelected()

    SheetDialog {
        id: sheetDialog
        onFinished: {

        }
    }

    SheetList {
        id: sheetList
        anchors.fill: parent
        onClicked : root.sheetSelected()
        onPressAndHold: {
            sheetDialog.editSheet(sheetList.selectedSheet)
        }
    }

    RoundButton {
        highlighted: true
        anchors.margins: 5
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        icon.source: "icon/add"
        onClicked: {
            sheetDialog.createSheet(sheets.addSheet())
        }
    }
}
