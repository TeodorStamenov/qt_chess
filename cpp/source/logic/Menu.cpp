#include "Menu.h"
#include "GameManager.h"

Menu::Menu(QObject* ui, GameManager& manager)
    : manager_(manager)
{
    QObject::connect(ui  , SIGNAL(newGame())
                   , this, SLOT(onNewGame()));

    QObject::connect(ui  , SIGNAL(loadGame())
                   , this, SLOT(onLoadGame()));
}

void Menu::onNewGame()
{
    manager_.startNewGame("", [this](){
        manager_.onStartNewGame();
    });
    qDebug() << "test";
}

void Menu::onLoadGame()
{
    manager_.loadSavedGames();
}
