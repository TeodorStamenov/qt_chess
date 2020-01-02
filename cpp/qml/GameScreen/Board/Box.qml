import QtQuick 2.0

import "../../Utils/Constants.js" as Const


Item {
    id: box

    property alias color: rect.color
    property alias piece: piece.source
    property alias state: rect.state
    property alias possible_move: possible_move.source
    property alias figWidth:  piece.width
    property alias figHeight:  piece.height

    property int boxX
    property int boxY
    property int indexB

    signal clickedBox(int x, int y)

    Rectangle {
        id: rect
        anchors.fill: parent
        state: "default"

        Image {
            id: piece
            anchors.centerIn: parent
        }

        Image {
            id: possible_move
            anchors.centerIn: parent
        }

        states: [
            State {
                name: "default"
                PropertyChanges {
                    target: rect
                    border.width: 0
                }
            },
            State {
                name: "clicked"
                PropertyChanges {
                    target: rect
                    border.width: 2
                    border.color: Const.COLOR_BOX_CLICKED
                }
            },
            State {
                name: "check"
                PropertyChanges {
                    target: rect
                    border.width: 2
                    border.color: "red"
                }
            }
        ]

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                if (board.state == "TurnHuman" && board.state !== "Pause") {
                    if (rect.state !== "check") {
                        rect.state == "default" ?
                                   rect.state = "clicked"
                                 : rect.state = "default";
                    }
                    box.clickedBox(boxX, boxY)
                }
            }
        }
    }

}

