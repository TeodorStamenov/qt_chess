import QtQuick 2.0
import QtMultimedia 5.12

import "../../Utils/Constants.js" as Const
import "../../Utils/Resources.js" as Rsrc


Item {
    width: Const.BOARD_WIDTH
    height: Const.BOARD_HEIGHT

    property alias boardState: board.state

    // inner border
    Rectangle {
        x: board.x - 2
        y: board.y - 2
        width: parent.width + 4
        height: parent.height + 4
        border.width: 5
        border.color: Const.COLOR_BOARDER
    }

    // actual board
    Rectangle {
        id: board
        objectName: "guiBoard"
        width: Const.BOARD_WIDTH
        height: Const.BOARD_HEIGHT
        border.width: Const.BOARD_MARGIN
        border.color: Const.COLOR_BOARD_INNER_BOARDER
        Component.onCompleted: state = "Pause"

        property int cachedIndex: -1

        // click on board
        signal clickedBoard(int index)

        onClickedBoard: {
            if (repeater.itemAt(index).state == "check") {
                if (cachedIndex != -1) {
                    repeater.itemAt(cachedIndex).state = "default";
                }
                return;
            }

            if (cachedIndex != -1 && cachedIndex != index) {
                repeater.itemAt(cachedIndex).state = "default";
            } else if (cachedIndex == -1) {
                repeater.itemAt(index).state = "clicked";
            }

            cachedIndex = index;
        }

        // cells
        Grid {
            anchors.top: parent.top
            anchors.topMargin: Const.BOARD_MARGIN
            anchors.left: parent.left
            anchors.leftMargin: Const.BOARD_MARGIN
            rows: Const.BOARD_ROW
            columns: Const.BOARD_COL

            Repeater {
                id: repeater
                model: Const.BOARD_ROW * Const.BOARD_COL

                Box {
                    boxX: Math.floor(index / Const.BOARD_ROW)
                    boxY: index % Const.BOARD_ROW
                    indexB: index
                    width: Const.BOX_SIZE
                    height: Const.BOX_SIZE
                    objectName: "b" + boxX + boxY
                    color: (boxX + boxY) % 2 == 0 ?
                               Const.COLOR_BOX_BLACK : Const.COLOR_BOX_WHITE
                    onClickedBox: {
                        board.clickedBoard(indexB)
                    }
                }
            }
        }

        // left side numbers
        Repeater {
            model: Const.BOARD_ROW
            Text {
                text: Const.BOARD_ROW - index
                x:5
                y:40 + index * Const.BOX_SIZE
                color: Const.COLOR_BOARD_TXT
                font.pointSize: Const.BOARD_TXT_SIZE
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // right side numbers
        Repeater {
            model: Const.BOARD_ROW
            Text {
                text: Const.BOARD_ROW - index
                x:505
                y:40 + index * Const.BOX_SIZE
                color: Const.COLOR_BOARD_TXT
                font.pointSize: Const.BOARD_TXT_SIZE
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // top side letters
        Repeater {
            model: Const.BOARD_COL
            Text {
                id: headTxt
                x:45 + index * Const.BOX_SIZE
                text: 'ABCDEFGH'.charAt(index)
                color: Const.COLOR_BOARD_TXT
                font.pointSize: Const.BOARD_TXT_SIZE
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // bottom side letter
        Repeater {
            model: Const.BOARD_COL
            Text {
                id: buttomTxt
                x:45 + index * Const.BOX_SIZE
                y:500
                text: 'ABCDEFGH'.charAt(index)
                color: Const.COLOR_BOARD_TXT
                font.pointSize: Const.BOARD_TXT_SIZE
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        // states
        states: [
            State {
                name: "TurnHuman"
                PropertyChanges {
                    target: textHuman
                    color: "#77b300"
                    font.bold: true
                    font.pointSize: 22
                }
                PropertyChanges {
                    target: textComputer
                    color: "#F6F0EA"
                    font.bold: false
                    font.pointSize: 16
                }
            },
            State {
                name: "TurnComputer"
                PropertyChanges {
                    target: textComputer
                    color: "#77b300"
                    font.bold: true
                    font.pointSize: 22
                }
                PropertyChanges {
                    target: textHuman
                    color: "#F6F0EA"
                    font.bold: false
                    font.pointSize: 16
                }
            },
            State {
                name: "Pause"
            }
        ]

        // label Computer
        Text {
            id: textComputer
            text: "Computer"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: - 40
            font.pointSize: 18
            color: Const.COLOR_TEXT
        }

        // label Human
        Text {
            id: textHuman
            text: "Human"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -40
            font.pointSize: 18
            color: Const.COLOR_TEXT
        }

        // sounds
        SoundEffect {
            id: soundPieceMove
            source: Rsrc.SOUND_PIECE_MOVE_2
        }

        SoundEffect {
            id: soundPieceSelect
            source: Rsrc.SOUND_PIECE_SELCET_2
        }

        // signal from Board.cpp: sendPieces
        function placePieces(pieces) {

            for (var i = 0; i < pieces.length; i += 2) {
                var index = parseInt(pieces[i]);
                var piece = pieces[i + 1];
                repeater.itemAt(index).piece = getPiece(piece);
            }

            board.state = "TurnHuman";
        }

        // signal from Board.cpp: sendPossibleMoves
        function placePossibleMoves(moves) {
            clearPossibleMoves();
            for (var m in moves) {
                repeater.itemAt(moves[m]).possible_move = Rsrc.POSSIBLE_MOVE;
            }
            soundPieceSelect.play()
        }

        // signal from Board.cpp: sendMoveOk
        function makeMove(fromIndex, toIndex) {
            clearPossibleMoves();
            var fig = repeater.itemAt(fromIndex).piece;
            repeater.itemAt(fromIndex).piece = "";
            repeater.itemAt(toIndex).piece = fig;
            if (cachedIndex != -1) {
                repeater.itemAt(cachedIndex).state = "default";
                cachedIndex = -1;
            }
            soundPieceMove.play();
        }

        // signal from Board.cpp: sendChangeTurn
        function changeTurn() {
            if (state == "TurnHuman") {
                state = "TurnComputer";
            } else {
                state = "TurnHuman";
            }
        }

        // signal from Board.cpp: sendStopGame
        function stopGame() {
            state = "Pause";
        }

        // signal from Board.cpp: sendSetCurrentTurn
        function setCurrentTurn(currentTurn) {
            state = currentTurn;
        }

        // signal from Board.cpp: sendPlacePiece
        function placePiece(index, piece) {
            repeater.itemAt(index).piece = getPiece(piece);
        }

        // signal from Board.cpp: sendCleanBoard
        function cleanBoard() {
            for (var i = 0; i < 64; i++) {
                var box = repeater.itemAt(i);
                box.piece = Rsrc.CLEAR_MOVE;
                box.state = "default";
                box.possible_move = Rsrc.EMPTY;
            }
        }

        // signal from Board.cpp: sendKingPosInCheck
        function kingPosInCheck(index)
        {
            repeater.itemAt(index).state = "check"
        }

        // signal from Board.cpp: sendClearKingInCheck
        function clearKingInCheck(index)
        {
            repeater.itemAt(index).state = "default"
        }

        // helper functions
        function clearPossibleMoves() {
            for (var i = 0; i < 64; i++) {
                repeater.itemAt(i).possible_move = Rsrc.CLEAR_MOVE;
            }
        }

        function getPiece(piece)
        {
            switch (piece)
            {
                case Const.WHITE_QUEEN: return Rsrc.WHITE_QUEEN_IMG;
                case Const.WHITE_KING:  return Rsrc.WHITE_KING_IMG;
                case Const.WHITE_KNIGHT:return Rsrc.WHITE_KNIGHT_IMG;
                case Const.WHITE_PAWN:  return Rsrc.WHITE_PAWN_IMG;
                case Const.WHITE_ROOK:  return Rsrc.WHITE_ROOK_IMG;
                case Const.WHITE_BISHOP:return Rsrc.WHITE_BISHOP_IMG;

                case Const.BLACK_QUEEN: return Rsrc.BLACK_QUEEN_IMG;
                case Const.BLACK_KING:  return Rsrc.BLACK_KING_IMG;
                case Const.BLACK_KNIGHT:return Rsrc.BLACK_KNIGHT_IMG;
                case Const.BLACK_PAWN:  return Rsrc.BLACK_PAWN_IMG;
                case Const.BLACK_ROOK:  return Rsrc.BLACK_ROOK_IMG;
                case Const.BLACK_BISHOP:return Rsrc.BLACK_BISHOP_IMG;
            }
            return Rsrc.EMPTY;
        }

    }
}
