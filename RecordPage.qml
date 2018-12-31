import QtQuick 2.0
import QtQuick.Controls 2.12

Page {
    id: root

    property alias sheet : recordList.sheet
    property alias selectedRecord: recordList.selectedRecord
    signal recordSelected()

    RecordDialog {
        id: recordDialog
        onFinished: {

        }
    }

    RecordList {
        id: recordList
        anchors.fill: parent
        sheet: root.recordSelected()
        onPressAndHold: {
            recordDialog.editRecord(recordList.selectedRecord)
        }
    }

    RoundButton {
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        icon.source: "icon/add"
        onClicked: {
            recordDialog.createRecord(sheet.addRecord())
        }
    }
}
