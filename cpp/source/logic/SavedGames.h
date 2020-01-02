#pragma once

#include <QVariant>
#include <QObject>
#include <QString>
#include <QJsonObject>

class GameManager;

class SavedGames : public QObject
{
    Q_OBJECT
public:
    SavedGames(QObject* ui, GameManager& manager);

public:
    void save(const int timeElapsed
            , const QString& fen
            , const QString& currentTurn
            , const int kingPosInCheck
            , const QString& capturedPiecesPlayer
            , const QString& capturedPiecesComputer);
    void loadSavedGames();

signals:
    void sendSavedGamesInfo(QVariant info);

public slots:
    void onLoad(int selectedRow);

private:
    QJsonObject savedGames_;
    GameManager& gameManager_;
};
