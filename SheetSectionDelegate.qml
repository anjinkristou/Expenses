
import QtQuick 2.7
import QtQuick.Controls 2.12

Pane {
    id: background

    Label {
        id: label
        text: section
        anchors.fill: parent
        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Qt.AlignVCenter
    }
}
