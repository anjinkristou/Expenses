import QtQuick 2.0
import QtQuick.Controls 2.12

Page {
    id: root

    property alias sheet : recordList.sheet

    RecordList {
        id: recordList
        anchors.fill: parent
        sheet: sheetList.selectedSheet
    }

    RoundButton {
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        icon.source: "icon/add"
        onClicked: {

        }
    }
}
