import QtQuick 2.9
import QtQuick.Window 2.2

import "MenuScreen"
import "GameScreen"
import "LoadGameScreen"

import "Utils/Constants.js" as Const

Window {
    id: window
    visible: true
    width: Const.WINDOW_WIDTH
    height: Const.WINDOW_HEIGHT
    title: qsTr("Chess")

    MenuScreen {
        id: menuScreen
        objectName: "guiMenu"
        visible: true

        onNewGame: {
            visible = false
            gameScreen.visible = true
        }

        onLoadGame: {
            menuScreen.opacity = 0.4
            loadGameScreen.visible = true
        }
    }

    GameScreen {
        id: gameScreen
        objectName: "guiInGameMenu"

        visible: false

        signal backMainMenu
        signal saveGame (int elapsedTime, string currentTurn)
        signal restartGame
        signal startGameTimer (int elapsedTime)
        signal setResultText (int result)

        onBackMainMenu: {
            menuScreen.visible = true
            visible = false
        }

        // sent signal from InGameMenu.cpp: sendStartTimer
        function onStartTimer(elapsedTime)
        {
            startGameTimer(elapsedTime);
        }

        // sent signal from InGameMenu.cpp: sendSetResult
        function setResult(result)
        {
            setResultText(result);
        }
    }

    LoadGameScreen {
        id: loadGameScreen
        objectName: "guiLoadGame"

        visible: false

        onLoad: {
            visible = false;
            menuScreen.visible = false;
            gameScreen.visible = true;
            menuScreen.opacity = 1;
        }

        onClose: {
            visible = false
            menuScreen.opacity = 1
        }
    }

}




















