#include "GameManager.h"
#include "utils/Logger.h"
#include "communication/commands/ClHandshakeCmd.h"
#include "communication/commands/ClNewGameCmd.h"
#include "communication/commands/ClEngineMakeMoveCmd.h"


namespace
{
    const QString LOG_FILE = "GameManager";

    void log(const QString& msg)
    {
        Logger::instance().log(LOG_FILE, msg);
    }

    bool isPlayerTurn(const char color)
    {
        return color == 'w' ? true : false;
    }
}

GameManager::GameManager(const ComponentsUI& componentsUI)
    : board_(componentsUI.find(UI_BOARD)->second, *this)
    , capturedPiecesPlayer_(componentsUI.find(UI_SIDE_PANEL_PLR)->second, *this)
    , capturedPiecesComputer_(componentsUI.find(UI_SIDE_PANEL_COMP)->second, *this)
    , menu_(componentsUI.find(UI_MENU)->second, *this)
    , inGameMenu_(componentsUI.find(UI_IN_GAME_MENU)->second, *this)
    , savedGames_(componentsUI.find(UI_LOAD_GAME)->second, *this)
    , connHandlerJSLib_(*this)
    , uciProcess_(*this)
{
    QObject::connect(&connHandlerJSLib_, &ConnectionHandler::connectionEstablished,
                     this, &GameManager::onConnectionEstablished);

    QObject::connect(&connHandlerJSLib_, &ConnectionHandler::connectionError,
                     this, &GameManager::onConnectionError);

    QObject::connect(&connHandlerJSLib_, &ConnectionHandler::connectionDisconnected,
                     this, &GameManager::onConnectionDisconnected);

    uciProcess_.processStart();
}

void GameManager::initialize()
{
    log("Try to connect JS lib");
    connHandlerJSLib_.connect();
}

void GameManager::startNewGame(const QString& fen, const StartGameCB& cb)
{
    startGameCallBack_ = cb;

    clean();

    ClNewGameCmd cmd;
    cmd.setFen(fen.toStdString());
    sendCommand(cmd);
}

void GameManager::onStartNewGame()
{
    inGameMenu_.startTimer(0);
}

void GameManager::saveGame(const int timeElapsed, const QString& currentTurn)
{
    savedGames_.save(timeElapsed
                   , board_.getCurrentFen()
                   , currentTurn
                   , board_.getKingPosInCheck()
                   , capturedPiecesPlayer_.getCapturedPieces()
                   , capturedPiecesComputer_.getCapturedPieces());
}

void GameManager::loadSavedGames()
{
    savedGames_.loadSavedGames();
}

void GameManager::onConnectionEstablished()
{
    log("Connected to JS lib");
    ClHandshakeCmd cmd;
    sendCommand(cmd);
}

void GameManager::onConnectionDisconnected()
{
    log("JS lib disconnected");
}

void GameManager::onConnectionError(QAbstractSocket::SocketError error)
{
    log(QString::number(error));
}

void GameManager::onUciEngineMove(QString move)
{
    ClEngineMakeMoveCmd cmd;
    cmd.init(move.toStdString());
    sendCommand(cmd);
}

void GameManager::sendCommand(CommandI &cmd)
{
    connHandlerJSLib_.sendCommand(cmd);
}

void GameManager::onSrvHandshake()
{
    log("Handshake.");
}

void GameManager::onSrvNewGameOk(const std::string& fen)
{
    board_.onParseFen(fen);
    board_.setCurrentFen(QString::fromStdString(fen));

    if (startGameCallBack_ != nullptr) {
        startGameCallBack_();
    }
}

void GameManager::onSrvPossibleMoves(const int index, const PossibleMoves& moves)
{
    board_.onPossibleMoves(index, moves);
}

void GameManager::onSrvMoveResult(const int res
                                , const int fromIndex
                                , const int toIndex
                                , const std::string& color
                                , const std::string& fen
                                , const std::string& capture
                                , const std::string& flags
                                , const std::string& oppCheck
                                , const int oppKingPos)
{
    if (res == 0) {
        beforeMove(fen);
        move(color.at(0), fromIndex, toIndex, flags, capture);
        afterMove(color.at(0), oppCheck, oppKingPos);

        if (color.at(0) == 'w') {
            uciProcess_.processRequest(fen);
            qDebug() << "waiting for engine";
        }

    } else {
        qDebug() << "Fail to move on requested index";
    }
}

void GameManager::engineMove(const QString& move)
{
    ClEngineMakeMoveCmd cmd;
    cmd.init(move.toStdString());
    sendCommand(cmd);
}

void GameManager::beforeMove(const std::string& fen)
{
    board_.setCurrentFen(QString::fromStdString(fen));

    if (board_.isKingInCheck())
    {
        board_.clearKingInCheck();
    }
}

void GameManager::move(const char color
                       , const int fromIndex
                       , const int toIndex
                       , const std::string& flags
                       , const std::string& capture)
{
    board_.onMoveOk(fromIndex, toIndex);

    if (flags.compare("c") == 0) {
        capturedPiece(color, capture.at(0));
    }
    else if(flags.compare("e") == 0) {
        enPassant(color, toIndex);
        capturedPiece(color, capture.at(0));
    }
    else if (flags.compare("np") == 0) {
        promotion(color, toIndex);
    }
    else if (flags.compare("k") == 0) {
        kingsideCastling(color);
    } else if (flags.compare("q") == 0) {
        queensideCastling(color);
    }
}

void GameManager::afterMove(const char color, const std::string& oppCheck, const int oppKingPos)
{
    if (oppCheck.compare("check") == 0) {
        board_.onKingInCheck(oppKingPos);
    }
    else if (oppCheck.compare("checkmate") == 0) {
        if (color == 'w') {
            inGameMenu_.sendResult(GameResult::GR_WON);
            board_.onKingInCheck(oppKingPos);
        } else {
            inGameMenu_.sendResult(GameResult::GR_LOST);
            board_.onKingInCheck(oppKingPos);
        }
        board_.stopGame();
        return;
    }
    else if (oppCheck.compare("stalemate") == 0) {
        inGameMenu_.sendResult(GameResult::GR_STALEMATE);
        board_.stopGame();
        return;
    }

    board_.nextTurn();
}

void GameManager::capturedPiece(const char color, const QChar capture)
{
    if (isPlayerTurn(color)) {
        capturedPiecesPlayer_.onCapturedPiece(capture);
    } else {
        capturedPiecesComputer_.onCapturedPiece(capture.toUpper());
    }
}

void GameManager::enPassant(const char color, const int index)
{
    if (isPlayerTurn(color)) {
        board_.onPlacePiece(index+8, QChar('\0'));
    } else {
        board_.onPlacePiece(index-8, QChar('\0'));
    }
}

void GameManager::promotion(const char color, const int index)
{
    if (isPlayerTurn(color)) {
        board_.onPlacePiece(index, QChar('Q'));
    } else {
        board_.onPlacePiece(index, QChar('q'));
    }
}

void GameManager::kingsideCastling(const char color)
{
    if (isPlayerTurn(color)) {
        board_.onMoveOk(63, 61); // from: H1 to: F1
    } else {
        board_.onMoveOk(7, 5);   // from: H8 to: F8
    }
}

void GameManager::queensideCastling(const char color)
{
    if (isPlayerTurn(color)) {
        board_.onMoveOk(56, 59);  // from: A1 to: D1
    } else {
        board_.onMoveOk(0, 3);    // from: A8 to: D8
    }
}

void GameManager::clean()
{
    board_.clean();
    capturedPiecesPlayer_.clean();
    capturedPiecesComputer_.clean();
    inGameMenu_.sendResult(GameResult::GR_NONE);
}

void GameManager::loadGameCompleted(const int timeElapsed
                                  , const int kingPosInCheck
                                  , const QString& currentTurn
                                  , const QString& capturedPiecesPlayer
                                  , const QString& capturedPiecesComputer)
{
    capturedPiecesPlayer_.setCaptutedPieces(capturedPiecesPlayer);
    capturedPiecesComputer_.setCaptutedPieces(capturedPiecesComputer);
    board_.setKingPosInCheck(kingPosInCheck);
    board_.setTurn(currentTurn);
    inGameMenu_.startTimer(timeElapsed);

    if (currentTurn == "TurnComputer") {
        uciProcess_.processRequest(board_.getCurrentFen().toStdString());
    }
}
