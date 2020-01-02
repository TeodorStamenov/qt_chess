#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QObject>

#include "source/logic/Board.h"
#include "logic/GameManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
//    qmlRegisterType<Board>("Board", 1, 0, "CppBoard");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *boardUI = engine.rootObjects().first()->findChildren<QObject*>("guiBoard").first();
    QObject *capturedPiecesPlrUI = engine.rootObjects().first()->findChildren<QObject*>("guiCapturedPiecesPlayer").first();
    QObject *capturedPiecesCompUI = engine.rootObjects().first()->findChildren<QObject*>("guiCapturedPiecesComputer").first();
    QObject *menuUI = engine.rootObjects().first()->findChildren<QObject*>("guiMenu").first();
    QObject *inGameMenuUI = engine.rootObjects().first()->findChildren<QObject*>("guiInGameMenu").first();
    QObject *loadGameUI = engine.rootObjects().first()->findChildren<QObject*>("guiLoadGame").first();

    GameManager::ComponentsUI componentsUI;
    componentsUI.emplace(GameManager::UI::UI_BOARD, boardUI);
    componentsUI.emplace(GameManager::UI::UI_SIDE_PANEL_PLR, capturedPiecesPlrUI);
    componentsUI.emplace(GameManager::UI::UI_SIDE_PANEL_COMP, capturedPiecesCompUI);
    componentsUI.emplace(GameManager::UI::UI_MENU, menuUI);
    componentsUI.emplace(GameManager::UI::UI_IN_GAME_MENU, inGameMenuUI);
    componentsUI.emplace(GameManager::UI::UI_LOAD_GAME, loadGameUI);

    GameManager mngr(componentsUI);
    mngr.initialize();
    return app.exec();
}
