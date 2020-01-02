#include "Board.h"
#include "GameManager.h"
#include "communication/commands/ClAskPossibleMovesCmd.h"
#include "communication/commands/ClMakeMoveCmd.h"

Board::Board(QObject* ui, GameManager& manager)
    : manager_(manager)
    , kingPosInCheck_(-1)
{
    QObject::connect(this, SIGNAL(sendPieces(QVariant))
                     ,ui ,SLOT(placePieces(QVariant)));

    QObject::connect(ui, SIGNAL(clickedBoard(int))
                     ,this ,SLOT(onClicked(int)));

    QObject::connect(this, SIGNAL(sendPossibleMoves(QVariant))
                     ,ui ,SLOT(placePossibleMoves(QVariant)));

    QObject::connect(this, SIGNAL(sendMoveOk(QVariant, QVariant))
                     ,ui ,SLOT(makeMove(QVariant, QVariant)));

    QObject::connect(this, SIGNAL(sendPlacePiece(QVariant, QVariant))
                     ,ui, SLOT(placePiece(QVariant, QVariant)));

    QObject::connect(this, SIGNAL(sendKingPosInCheck(QVariant))
                     ,ui, SLOT(kingPosInCheck(QVariant)));

    QObject::connect(this, SIGNAL(sendClearKingInCheck(QVariant))
                     ,ui, SLOT(clearKingInCheck(QVariant)));

    QObject::connect(this, SIGNAL(sendChangeTurn())
                     ,ui, SLOT(changeTurn()));

    QObject::connect(this, SIGNAL(sendCleanBoard())
                     ,ui, SLOT(cleanBoard()));

    QObject::connect(this, SIGNAL(sendStopGame())
                     ,ui, SLOT(stopGame()));

    QObject::connect(this, SIGNAL(sendSetCurrentTurn(QVariant))
                     ,ui, SLOT(setCurrentTurn(QVariant)));
}

void Board::onParseFen(const std::string &fen)
{
    /*fen algorithm*/
    QVariantList pieces;
    int boardIndex = 0;
    for (size_t i = 0; i < fen.size(); i++) {
        const QChar piece = fen.at(i);

        if (piece.isSpace()) {
            break;
        }

        if (piece == '/') {
            continue;
        }

        if (piece.isDigit()) {
            boardIndex += static_cast<int>(piece.toLatin1()) - 48;
            continue;
        }

        pieces << boardIndex << piece;
        boardIndex++;
    }

    emit sendPieces(QVariant::fromValue(pieces));
}

void Board::onClicked(int index)
{
    if (movesForIndex.originIndex == index) {
        return;
    }

    const auto& moves = movesForIndex.possibleMoves;

    const bool res =
            std::find(moves.begin(), moves.end(), index) != moves.end();

    if (res) {
        ClMakeMoveCmd cmd;
        cmd.init(movesForIndex.originIndex, index);
        manager_.sendCommand(cmd);

        movesForIndex.originIndex = -1;
        movesForIndex.possibleMoves.clear();
    } else {
        ClAskPossibleMovesCmd cmd;
        cmd.init(index);
        manager_.sendCommand(cmd);
    }
}

void Board::onPossibleMoves(const int index, const PossibleMoves& moves)
{
    movesForIndex.originIndex = index;
    movesForIndex.possibleMoves = moves;
    emit sendPossibleMoves(QVariant::fromValue(moves));
}

void Board::onMoveOk(const int fromIndex, const int toIndex)
{
    emit sendMoveOk(QVariant::fromValue(fromIndex),
                    QVariant::fromValue(toIndex));
}

void Board::onPlacePiece(const int index, const QChar piece)
{
    emit sendPlacePiece(QVariant::fromValue(index),
                        QVariant::fromValue(piece));
}

void Board::onKingInCheck(const int kingPos)
{
    kingPosInCheck_ = kingPos;
    emit sendKingPosInCheck(QVariant::fromValue(kingPos));
}

void Board::clearKingInCheck()
{
    emit sendClearKingInCheck(kingPosInCheck_);
    kingPosInCheck_ = -1;
}

void Board::clean()
{
    movesForIndex.originIndex = -1;
    movesForIndex.possibleMoves.clear();
    fen_.clear();
    emit sendCleanBoard();
}

bool Board::isKingInCheck()
{
    return kingPosInCheck_ != -1 ? true : false;
}

void Board::setCurrentFen(const QString& fen)
{
    fen_ = fen;
}

const QString& Board::getCurrentFen() const
{
    return fen_;
}

int Board::getKingPosInCheck() const
{
    return kingPosInCheck_;
}

void Board::setKingPosInCheck(const int kingPosInCheck)
{
    if (kingPosInCheck != -1) {
        kingPosInCheck_ = kingPosInCheck;
        emit sendKingPosInCheck(QVariant::fromValue(kingPosInCheck));
    }
}

void Board::nextTurn()
{
    emit sendChangeTurn();
}

void Board::stopGame()
{
    emit sendStopGame();
}

void Board::setTurn(const QString& currentTurn)
{
    emit sendSetCurrentTurn(QVariant::fromValue(currentTurn));
}
