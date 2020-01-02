#pragma once

#include <QObject>
#include <QVariant>
#include <QString>

#include "utils/PossibleMoves.h"

class GameManager;

class Board : public QObject
{
    Q_OBJECT
public:
    Board(QObject* ui, GameManager& manager);

    void onParseFen(const std::string& fen);
    void onPossibleMoves(const int index, const PossibleMoves& moves);
    void onMoveOk(const int fromIndex, const int toIndex);
    void onPlacePiece(const int index, const QChar piece);
    void onKingInCheck(const int kingPos);
    void clearKingInCheck();
    void clean();
    bool  isKingInCheck();
    void  setCurrentFen(const QString& fen);
    const QString& getCurrentFen() const;
    int      getKingPosInCheck() const;
    void setKingPosInCheck(const int kingPosInCheck);
    void nextTurn();
    void stopGame();
    void setTurn(const QString& currentTurn);

signals:
    void sendPieces(QVariant message);
    void sendPossibleMoves(QVariant message);
    void sendMoveOk(QVariant fromIndex, QVariant toIndex);
    void sendPlacePiece(QVariant index, QVariant newPiece);
    void sendKingPosInCheck(QVariant index);
    void sendChangeTurn();
    void sendClearKingInCheck(QVariant);
    void sendCleanBoard();
    void sendStopGame();
    void sendSetCurrentTurn(QVariant);

public slots:
    void onClicked(int index);

private:
    GameManager& manager_;

    int         kingPosInCheck_;
    QString     fen_;

    struct {
        int originIndex;
        PossibleMoves possibleMoves;
    } movesForIndex;
};
