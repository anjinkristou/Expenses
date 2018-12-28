import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

GridLayout {
    id: grid

    property alias name: name
    property alias submittedDate: submittedDate
    property int minimumInputSize: 120
    property string placeholderText: qsTr("<enter>")

    rows: 2
    columns: 2

    Label {
        text: qsTr("Name")
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    TextField {
        id: name
        focus: true
        Layout.fillWidth: true
        Layout.minimumWidth: grid.minimumInputSize
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        placeholderText: grid.placeholderText
    }

    Label {
        text: qsTr("Submitted Date")
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    TextField {
        id: submittedDate
        focus: true
        Layout.fillWidth: true
        Layout.minimumWidth: grid.minimumInputSize
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        placeholderText: grid.placeholderText
    }
}
