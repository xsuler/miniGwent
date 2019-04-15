import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("GameActor")

    MainFrame {
        id:idMainframe
    }
    onClosing: {
        GA.close()
    }
}
