import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

GridLayout {
    id: grid

    property alias amount: amount
    property int minimumInputSize: 120

    rows: 2
    columns: 2

    Label {
        text: qsTr("Amount")
        Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
    }

    SpinBox {
        id: amount
        focus: true
        from: 0
        value: 0
        to: 10000

        property int decimals: 2
        property real realValue: value / 100

        validator: DoubleValidator {
            bottom: Math.min(amount.from, amount.to)
            top:  Math.max(amount.from, amount.to)
        }

        textFromValue: function(value, locale) {
            return Number(value / 100).toLocaleString(locale, 'f', amount.decimals)
        }

        valueFromText: function(text, locale) {
            return Number.fromLocaleString(locale, text) * 100
        }
    }
}
