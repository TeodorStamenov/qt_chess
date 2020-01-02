import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4
import QtMultimedia 5.12
import QtGraphicalEffects 1.0

import "../../Utils/Constants.js" as Const
import "../../Utils/Resources.js" as Rsrc
import "../../Utils/Utils.js"     as Utils

Item {
    anchors.fill: parent

    property alias txt: textResult.text

    Rectangle {
        anchors.fill: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#28313B" }
            GradientStop { position: 1.0; color: "#485461" }
        }

        SoundEffect {
            id: soundEffect
            source: Rsrc.SOUND_BUTTON_2
        }

        Timer {
            id: timer
            property var count: 0

            interval: 1000; running: true; repeat: true
            onTriggered: {
                count++;
                textTimer.text = "Timer: " + Utils.formatTime(count);
            }
            Component.onCompleted: stop()
            onRunningChanged:
            {
                textTimer.text = "Timer: " + Utils.formatTime(count);
            }
        }

        Text {
            id: textResult
            anchors.top: parent.top
            anchors.topMargin: 320
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 26
            font.bold: true
            color: "#f2f2f2"
        }

        Text {
            id: textTimer
            anchors.fill: capturedPieceComp
            anchors.top: capturedPieceComp.top
            anchors.topMargin: - 80
            font.pointSize: 14
            color: "#f2f2f2"
            text: "Timer: " + Utils.formatTime(timer.count)
        }

        GridLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20

            columns: 1
            rows: 3

            width: 200

            Button {
                Layout.fillWidth: true
                implicitHeight: 50
                text: "Main Menu"
                onClicked: {
                    soundEffect.play()
                    backMainMenu()
                }
            }

            Button {
                Layout.fillWidth: true
                implicitHeight: 50
                text: "Save Game"
                onClicked: {
                    if (board.boardState != "Pause") {
                        soundEffect.play()
                        saveGame(timer.count, board.boardState)
                    }
                }
            }

            Button {
                Layout.fillWidth: true
                implicitHeight: 50
                text: "Restart Game"
                onClicked: {
                    soundEffect.play()
                    restartGame()
                }
            }

            Button {
                Layout.fillWidth: true
                implicitHeight: 50
                text: "Quit"
                onClicked: {
                    soundEffect.play()
                    Qt.quit()
                }
            }
        }

        CapturedPieces {
            id: capturedPieceComp
            objectName: "guiCapturedPiecesComputer"
            anchors.top: parent.top
            anchors.topMargin: Const.WINDOW_HEIGHT - Const.RESULT_HEIGHT * 2 - 60;
            anchors.left: parent.left
            anchors.leftMargin: 32
            label: "Computer captured"
        }


        CapturedPieces {
            id: capturedPiecePlayer
            objectName: "guiCapturedPiecesPlayer"
            anchors.top: parent.top
            anchors.topMargin: Const.WINDOW_HEIGHT - Const.RESULT_HEIGHT - 20
            anchors.left: parent.left
            anchors.leftMargin: 32
            label: "Player captured"
        }
    }

    Connections {
        target: gameScreen
        onStartGameTimer: {
            timer.count = elapsedTime;
            timer.restart()
        }
        onSetResultText: {
            switch (result) {
                case 0: textResult.text = Const.TEXT_WON;  break;
                case 1: textResult.text = Const.TEXT_LOST; break;
                case 2: textResult.text = Const.TEXT_STALEMATE; break;
                case 3: textResult.text = Const.TEXT_NONE; break;
            }
        }
    }

}
