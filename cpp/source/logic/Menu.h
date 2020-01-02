#pragma once

#include <QObject>
#include <QVariant>

class GameManager;

class Menu : public QObject
{
    Q_OBJECT
public:
    Menu(QObject* ui, GameManager& manager);

public slots:
    void onNewGame();
    void onLoadGame();

private:
    GameManager& manager_;
};
