import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

GridLayout {
    id: grid

    property alias amount: amount
    property int minimumInputSize: 120
    property string placeholderText: qsTr("0.0")

    rows: 2
    columns: 2

    Label {
        text: qsTr("Amount") + ":"
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    RowLayout{
        Layout.fillWidth: true
        spacing: 4

        Text {
            text: "€"
        }
        TextField {
            id: amount
            focus: true
            Layout.fillWidth: true
            Layout.minimumWidth: grid.minimumInputSize
            Layout.alignment: Qt.AlignRight | Qt.AlignBaseline
            placeholderText: grid.placeholderText
            validator : RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
        }
    }
}
