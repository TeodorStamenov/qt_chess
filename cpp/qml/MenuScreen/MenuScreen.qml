import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtMultimedia 5.12

import "../Utils/Constants.js" as Const
import "../Utils/Resources.js" as Rsrc

Item {
    anchors.fill: parent

    signal newGame
    signal loadGame

    SoundEffect {
        id: soundEffect
        source: Rsrc.SOUND_BUTTON_2
    }

    Rectangle {
        anchors.fill: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#28313B" }
            GradientStop { position: 1.0; color: "#485461" }
        }


        GridLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 100

            columns: 1
            rows: 3
            width: 400

            Button {
                Layout.fillWidth: true
                implicitHeight: 100
                font.pointSize: 30;
                font.bold: true
                text: "New Game"
                onClicked: {
                    soundEffect.play()
                    newGame()
                }
            }

            Button {
                Layout.fillWidth: true
                implicitHeight: 100
                font.pointSize: 30;
                font.bold: true
                text: "Load Game"
                onClicked: {
                    soundEffect.play()
                    loadGame()
                }
            }

            Button {
                Layout.fillWidth: true
                implicitHeight: 100
                font.pointSize: 30;
                font.bold: true
                text: "Quit"
                onClicked:  {
                    soundEffect.play()
                    Qt.quit()
                }
            }
        }
    }

}
