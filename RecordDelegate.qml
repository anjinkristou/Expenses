import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

SwipeDelegate {
    id: delegate

    signal editRequested(int index)
    signal deleteRequested(int index)

    contentItem: RowLayout {
        spacing: 10

        Text {
            text: "€" + amount
            font.bold: true
            elide: Text.ElideRight
            Layout.fillWidth: true
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
        text: qsTr("Edit")
        color: "white"
        verticalAlignment: Label.AlignVCenter
        padding: 12
        height: parent.height

        SwipeDelegate.onClicked: {
            delegate.swipe.close()
            delegate.editRequested(index)
        }

        background: Rectangle {
            color: renameLabel.SwipeDelegate.pressed ? Qt.darker("#00C853", 1.1) : "#00C853"
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
