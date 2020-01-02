#pragma once

#include "communication/ConnectionHandler.h"
#include "communication/CommandHandlerI.h"
#include "logic/Board.h"
#include "logic/CapturedPieces.h"
#include "logic/Menu.h"
#include "logic/InGameMenu.h"
#include "logic/SavedGames.h"
#include "logic/EngineProcess.h"
#include <list>

class GameManager : public QObject, public CommandHandlerI
{
    Q_OBJECT
public:
    enum UI
    {
        UI_BOARD            = 0,
        UI_SIDE_PANEL_PLR   = 1,
        UI_SIDE_PANEL_COMP  = 2,
        UI_MENU             = 3,
        UI_IN_GAME_MENU     = 4,
        UI_LOAD_GAME        = 5,
    };

    using ComponentsUI = std::map<UI, QObject*>;

    using StartGameCB = std::function<void()>;

public:
    explicit GameManager(const ComponentsUI& componentsUI);

    void initialize();
    void startNewGame(const QString& fen, const StartGameCB& cb);
    void onStartNewGame();
    void saveGame(const int timeElapsed, const QString& currentTurn);
    void loadSavedGames();
    void sendCommand(CommandI& cmd);
    void loadGameCompleted(const int timeElapsed
                         , const int kingPosInCheck
                         , const QString& currentTurn
                         , const QString& capturedPiecesPlayer
                         , const QString& capturedPiecesComputer);
    void engineMove(const QString& move);

public slots:
    void onConnectionEstablished();
    void onConnectionDisconnected();
    void onConnectionError(QAbstractSocket::SocketError error);
    void onUciEngineMove(QString move);

private:
    // CommandHandlerI
    virtual void onSrvHandshake() override;
    virtual void onSrvNewGameOk(const std::string& fen) override;
    virtual void onSrvPossibleMoves(const int index, const PossibleMoves& moves) override;
    virtual void onSrvMoveResult(const int res
                               , const int fromIndex
                               , const int toIndex
                               , const std::string& color
                               , const std::string& fen
                               , const std::string& capture
                               , const std::string& flags
                               , const std::string& oppCheck
                               , const int oppKingPos) override;

private:
    void beforeMove(const std::string& fen);

    void move(const char color
            , const int fromIndex
            , const int toIndex
            , const std::string& flags
            , const std::string& capture);

    void afterMove(const char color, const std::string& oppCheck, const int oppKingPos);

    void capturedPiece(const char color, const QChar capture);
    void enPassant(const char color, const int index);
    void promotion(const char color, const int index);
    void kingsideCastling(const char color);
    void queensideCastling(const char color);
    void clean();

private:
    Board board_;
    CapturedPieces capturedPiecesPlayer_;
    CapturedPieces capturedPiecesComputer_;
    Menu menu_;
    InGameMenu inGameMenu_;
    SavedGames savedGames_;
    ConnectionHandler connHandlerJSLib_;
    EngineProcess uciProcess_;
    StartGameCB startGameCallBack_;
};
