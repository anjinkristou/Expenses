import QtQuick 2.0
import QtQuick.Controls 2.12

import com.kristou.expense 1.0

ListView {
    id: listView

    property alias sheet : recordModel.sheet
    signal clicked(int index)

    delegate: RecordDelegate {
        id: delegate
        width: listView.width

        Connections {
            target: delegate
            onClicked: listView.clicked(index)
        }
    }

    model: RecordModel {
        id: recordModel
    }

    ScrollBar.vertical: ScrollBar { }
}
