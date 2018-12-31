import QtQuick 2.0
import QtQuick.Controls 2.12

import com.kristou.expense 1.0

Dialog {
    id: dialog

    property Record record: null

    signal finished()

    function createRecord(record) {
        dialog.record = record
        form.amount.value = 0;

        dialog.title = qsTr("Add Record");
        dialog.open();
    }

    function editRecord(record) {
        dialog.record = record
        form.amount.value = record.amount;

        dialog.title = qsTr("Edit Record");
        dialog.open();
    }

    x: (parent.width - width) / 2
    y: 10

    focus: true
    modal: true
    title: qsTr("Add Record")
    standardButtons: Dialog.Ok | Dialog.Cancel

    contentItem: RecordForm {
        id: form
    }

    onAccepted: {
        if(dialog.record){
            record.amount = form.amount.realValue
        }

        dialog.record = null

        dialog.finished()
    }

}
