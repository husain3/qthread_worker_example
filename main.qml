import QtQuick 2.5
import QtQuick.Controls 1.4
import Workers 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SystemPalette {
        id: pal
        colorGroup: SystemPalette.Active
    }

    Worker {
        id: worker;
    }

    Button {
        id: button
        text: qsTr("Process")
        anchors.centerIn: parent

        onClicked: worker.process();
    }

    Text {
        text: worker.data
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: button.bottom
        anchors.topMargin: 20
    }
}
