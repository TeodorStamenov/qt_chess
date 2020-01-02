import QtQuick 2.0
import QtGraphicalEffects 1.0

import "InGameMenu"
import "Board"

import "../Utils/Constants.js" as Const

Item {
    anchors.fill: parent

    // right side of the screen
    Rectangle {
        anchors.fill: parent

        // background color
        LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end:   Qt.point(parent.width, 0)

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#031E07" }
                GradientStop { position: 1.0; color: "#185A22" }
            }
        }

        Board {
            id: board
            anchors.top: parent.top
            anchors.topMargin: Const.BOARD_MARGIN_TOP
            anchors.right: parent.right
            anchors.rightMargin: Const.BOARD_MARGIN_RIGHT
        }
    }

    // left side of the screen
    Rectangle {
        width: Const.WINDOW_WIDTH - Const.BOARD_WIDTH - Const.BOARD_MARGIN_RIGHT - 30
        height: parent.height

        InGameMenu {
        }
    }

}
