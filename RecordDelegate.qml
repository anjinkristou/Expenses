import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

ItemDelegate {
    id: delegate

    contentItem: RowLayout {
        spacing: 10

        Text {
            text: purpose
            font.bold: true
            elide: Text.ElideRight
            Layout.fillWidth: true
        }

    }
}
