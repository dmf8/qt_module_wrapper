import QtQuick 2.0
import QtQuick.Controls 2.15

TextField {
    signal wheelIncrease(int step)
    signal wheelDecrease(int step)
    signal wheelBatchFinished()
    property int batch_interval: 200

    MouseArea {
        anchors.fill: parent
        onClicked: {
            parent.forceActiveFocus()
        }

        onWheel: {
            var step = wheel.angleDelta.y / 120
            if (step > 0)
                wheelIncrease(step)
            if (step < 0)
                wheelDecrease(step)
            _timer.restart()
        }
    }
    onEditingFinished: {
        console.log(text)
    }

    Timer {
        id: _timer
        interval: batch_interval
        onTriggered: wheelBatchFinished()
    }
}
