#include "InGameMenu.h"
#include "GameManager.h"


InGameMenu::InGameMenu(QObject* ui, GameManager& manager)
    : manager_(manager)
{
    QObject::connect(ui  , SIGNAL(restartGame())
                   , this, SLOT(onRestartGame()));

    QObject::connect(ui  , SIGNAL(saveGame(int, QString))
                   , this, SLOT(onSaveGame(int, QString)));

    QObject::connect(this , SIGNAL(sendStartTimer(QVariant))
                   , ui   , SLOT(onStartTimer(QVariant)));

    QObject::connect(this, SIGNAL(sendSetResult(QVariant))
                   , ui, SLOT(setResult(QVariant)));
}

void InGameMenu::onRestartGame()
{
    manager_.startNewGame("", [this](){
        manager_.onStartNewGame();
    });
}

void InGameMenu::onSaveGame(int elapsedTime, QString currentTurn)
{
    manager_.saveGame(elapsedTime, currentTurn);
}

void InGameMenu::startTimer(int elapsedTime)
{
    emit sendStartTimer(QVariant::fromValue(elapsedTime));
}

void InGameMenu::sendResult(GameResult result)
{
    emit sendSetResult(QVariant::fromValue(static_cast<int>(result)));
}
