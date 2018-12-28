import QtQuick 2.0
import QtQuick.Controls 2.12

import com.kristou.expense 1.0

ListView {
    id: listView

    property alias sheets : sheetModel.sheetCollection
    property Sheet selectedSheet: null
    signal clicked(int index)
    signal pressAndHold(int index)

    section.property: "submitted_date"
    section.criteria: ViewSection.FullString
    section.delegate: SheetSectionDelegate {
        width: listView.width
    }

    delegate: SheetDelegate {
        id: delegate
        width: listView.width

        Connections {
            target: delegate
            onClicked: {
                selectedSheet = sheets.sheetAt(index)
                listView.clicked(index)
            }
            onPressAndHold: {
                selectedSheet = sheets.sheetAt(index)
                listView.pressAndHold(index)
            }
            onDeleteRequested: {
                sheets.removeAt(index)
            }
            onEditRequested: {
                selectedSheet = sheets.sheetAt(index)
                listView.pressAndHold(index)
            }
        }
    }

    model: SheetModel {
        id: sheetModel
    }

    ScrollBar.vertical: ScrollBar { }
}
