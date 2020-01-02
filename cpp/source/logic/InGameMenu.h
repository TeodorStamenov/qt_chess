#pragma once

#include <QObject>
#include <QVariant>
#include "utils/GameResult.h"

class GameManager;

class InGameMenu : public QObject
{
    Q_OBJECT
public:
    InGameMenu(QObject* ui, GameManager& manager);

    void startTimer(int elapsedTime);
    void sendResult(GameResult result);

signals:
    void sendStartTimer(QVariant elapsedTime);
    void sendSetResult(QVariant);

public slots:
    void onRestartGame();
    void onSaveGame(int elapsedTime, QString currentTurn);

private:
    GameManager& manager_;
};
