import QtQuick 2.0
import QtQuick.Controls 2.12

import com.kristou.expense 1.0

ListView {
    id: listView

    property alias sheet : recordModel.sheet
    property Record selectedRecord: null
    signal clicked(int index)
    signal pressAndHold(int index)

    delegate: RecordDelegate {
        id: delegate
        width: listView.width

        Connections {
            target: delegate
            onClicked: {
                selectedRecord = sheet.recordAt(index)
                listView.clicked(index)
            }
            onPressAndHold: {
                selectedRecord = sheet.recordAt(index)
                listView.pressAndHold(index)
            }
            onDeleteRequested: {
                sheet.removeAt(index)
            }
            onEditRequested: {
                selectedRecord = sheet.recordAt(index)
                listView.pressAndHold(index)
            }
        }
    }

    model: RecordModel {
        id: recordModel
    }

    ScrollBar.vertical: ScrollBar { }
}
