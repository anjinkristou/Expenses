
import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

SwipeDelegate {
    id: delegate

    clip: true

    signal editRequested(int index)
    signal deleteRequested(int index)

    contentItem: RowLayout {
        spacing: 10

        Text {
            text: name
            font.bold: true
            elide: Text.ElideRight
            Layout.fillWidth: true
        }


        Rectangle {
            width: 30
            height: 30
            radius: 30
            color: "gray"
            Text {
                anchors.centerIn: parent
                text: record_count
                elide: Text.ElideRight
            }
        }
        Text {
            text: "€" + total_amount
            font.bold: true
            elide: Text.ElideRight
        }

        Rectangle {
            width: 50
            height: 30
            color: "yellow"
            radius: 5
            Text {
                anchors.centerIn: parent
                text: status
            }
        }

    }

    ListView.onRemove: SequentialAnimation {
        PropertyAction {
            target: delegate
            property: "ListView.delayRemove"
            value: true
        }
        NumberAnimation {
            target: delegate
            property: "height"
            to: 0
            easing.type: Easing.InOutQuad
        }
        PropertyAction {
            target: delegate
            property: "ListView.delayRemove"
            value: false
        }
    }

    swipe.left: Label {
        id: renameLabel
        text: qsTr("Rename")
        color: "white"
        verticalAlignment: Label.AlignVCenter
        padding: 12
        height: parent.height

        SwipeDelegate.onClicked: {
            delegate.swipe.close()
            delegate.editRequested(index)
        }

        background: Rectangle {
            color: renameLabel.SwipeDelegate.pressed ? Qt.darker("#1565C0", 1.1) : "#1565C0"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                delegate.swipe.close()
                delegate.editRequested(index)
            }
        }
    }

    swipe.right: Label {
        id: deleteLabel
        text: qsTr("Delete")
        color: "white"
        verticalAlignment: Label.AlignVCenter
        padding: 12
        height: parent.height
        anchors.right: parent.right

        SwipeDelegate.onClicked: {
            delegate.swipe.close()
            delegate.deleteRequested(index)
        }

        background: Rectangle {
            color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                delegate.swipe.close()
                delegate.deleteRequested(index)
            }
        }
    }
}
