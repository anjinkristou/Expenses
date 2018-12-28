import QtQuick 2.0
import QtQuick.Controls 2.12

import com.kristou.expense 1.0

Dialog {
    id: dialog

    property Sheet sheet: null

    signal finished()

    function createSheet(sheet) {
        dialog.sheet = sheet
        form.name.clear();
        form.submittedDate.clear();

        dialog.title = qsTr("Add Sheet");
        dialog.open();
    }

    function editSheet(sheet) {
        dialog.sheet = sheet
        form.name.text = sheet.name;
        form.submittedDate.text = sheet.submittedDate;

        dialog.title = qsTr("Edit Sheet");
        dialog.open();
    }

    x: (parent.width - width) / 2
    y: 10

    focus: true
    modal: true
    title: qsTr("Add Sheet")
    standardButtons: Dialog.Ok | Dialog.Cancel

    contentItem: SheetForm {
        id: form
    }

    onAccepted: {
        if(dialog.sheet){
            sheet.name = form.name.text
        }

        dialog.sheet = null

        dialog.finished()
    }

}
