import QtQuick 2.0
import QtGraphicalEffects 1.0

import "../Board"
import "../../Utils/Constants.js" as Const
import "../../Utils/Resources.js" as Rsrc


Item {

    property alias label: label.text

    Rectangle {
        id: result
        width: Const.RESULT_WIDTH
        height: Const.RESULT_HEIGHT
        border.width: 2
        border.color: Const.COLOR_CAPTURED_BORDER

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#28313B" }
            GradientStop { position: 1.0; color: "#485461" }
        }

        Text {
            id: label
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: -20
            color: Const.COLOR_TEXT
            font.bold: false
            font.pointSize: 12
        }

        Row {
            id: row1
            x: parent.x + 15

            Repeater {
                id: repeater1
                model:8

                Box {
                    x: parent.x + index * 46
                    y: result.y + 25
                    figWidth: 45
                    figHeight: 45
                }
            }
        }

        Row {
            id: row2
            x: parent.x + 15

            Repeater {
                id: repeater2
                model:8

                Box {
                    x: parent.x + index * 46
                    y: result.y + 70
                    figWidth: 45
                    figHeight: 45
                }
            }
        }
    }

    // signal from CapturedPieces.cpp: sendCapturedPiece
    function capturedPiece(pieces) {
        for (var piece in pieces) {
            var flag = false;

            for (var i = 0; i < 8; i++) {
                if (repeater1.itemAt(i).piece == Rsrc.EMPTY) {
                    repeater1.itemAt(i).piece = getPiece(pieces[piece]);
                    flag = true;
                    break;
                }
            }

            if (flag) {
                continue;
            }

            for (var t = 0; t < 8; t++) {
                if (repeater2.itemAt(t).piece == Rsrc.EMPTY) {
                    repeater2.itemAt(t).piece = getPiece(piece[piece]);
                    break;
                }
            }

        }
    }

    // signal from CapturedPieces.cpp: sendCleanPieces
    function cleanPieces() {
        for (var i = 0; i < 8; i++) {
            repeater1.itemAt(i).piece = Rsrc.EMPTY;
        }
        for (var t = 0; t < 8; t++) {
            repeater2.itemAt(t).piece = Rsrc.EMPTY;
        }
    }

    // helper function
    function getPiece(piece) {
        switch (piece)
        {
            case Const.WHITE_QUEEN:  return Rsrc.WHITE_QUEEN_IMG;
            case Const.WHITE_KING:   return Rsrc.WHITE_KING_IMG;
            case Const.WHITE_KNIGHT: return Rsrc.WHITE_KNIGHT_IMG;
            case Const.WHITE_PAWN:   return Rsrc.WHITE_PAWN_IMG;
            case Const.WHITE_ROOK:   return Rsrc.WHITE_ROOK_IMG;
            case Const.WHITE_BISHOP: return Rsrc.WHITE_BISHOP_IMG;

            case Const.BLACK_QUEEN:  return Rsrc.BLACK_QUEEN_IMG;
            case Const.BLACK_KING:   return Rsrc.BLACK_KING_IMG;
            case Const.BLACK_KNIGHT: return Rsrc.BLACK_KNIGHT_IMG;
            case Const.BLACK_PAWN:   return Rsrc.BLACK_PAWN_IMG;
            case Const.BLACK_ROOK:   return Rsrc.BLACK_ROOK_IMG;
            case Const.BLACK_BISHOP: return Rsrc.BLACK_BISHOP_IMG;
        }
    }
}
