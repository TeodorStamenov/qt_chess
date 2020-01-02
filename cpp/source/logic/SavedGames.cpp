#include "SavedGames.h"
#include "GameManager.h"
#include <QtDebug>
#include <QDateTime>
#include <QDir>
#include <QJsonArray>
#include <QJsonParseError>


namespace
{
    const QString DIR_NAME  = "SavedGames";
    const QString FILE_NAME = "SavedGames.json";
    const int     MAX_GAMES = 10;

    QString getCurrentTime()
    {
        QDateTime time = QDateTime::currentDateTime();
        return time.toString();
    }

    QJsonObject openJson()
    {
        QFile file(FILE_NAME);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
            file.close();

            if (err.error) {
                qDebug() << "error while parsing json file: " << err.errorString();
            } else {
                return doc.object();
            }

        } else {
            qDebug() << "can not open json file: " << file.fileName();
        }

        return QJsonObject();
    }

    void saveJson(const QJsonObject& jsonObject)
    {
        QFile file(FILE_NAME);
        if (file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate)) {
            QJsonDocument doc(jsonObject);
            file.write(doc.toJson());
        } else {
            qDebug() << "can not open json file: " << file.fileName();
        }
        file.close();
    }
}

SavedGames::SavedGames(QObject* ui, GameManager& gameManager)
    : gameManager_(gameManager)
{
    QObject::connect(this, SIGNAL(sendSavedGamesInfo(QVariant))
                   , ui  , SLOT(savedGamesDates(QVariant)));

    QObject::connect(ui, SIGNAL(load(int))
                   , this, SLOT(onLoad(int)));
}

void SavedGames::save(const int timeElapsed
                    , const QString& fen
                    , const QString& currentTurn
                    , const int kingPosInCheck
                    , const QString& capturedPiecesPlayer
                    , const QString& capturedPiecesComputer)
{
    QJsonObject jsonObject = openJson();

    QJsonArray games = jsonObject.find("Games").value().toArray();

    if (games.size() >= MAX_GAMES) {
        games.pop_back();
    }

    QJsonObject game;
    game.insert("Date", QJsonValue::fromVariant(getCurrentTime()));
    game.insert("Fen" , QJsonValue::fromVariant(fen));
    game.insert("TimeElapsed", QJsonValue::fromVariant(timeElapsed));
    game.insert("CapturedPiecesPlayer", QJsonValue::fromVariant(capturedPiecesPlayer));
    game.insert("CapturedPiecesComputer", QJsonValue::fromVariant(capturedPiecesComputer));
    game.insert("KingPosInCheck", QJsonValue::fromVariant(kingPosInCheck));
    game.insert("CurrentTurn", QJsonValue::fromVariant(currentTurn));
    games.push_front(game);

    jsonObject.insert("Games", games);

    saveJson(jsonObject);
}

void SavedGames::loadSavedGames()
{
    savedGames_ = openJson();
    emit sendSavedGamesInfo(savedGames_);
}

void SavedGames::onLoad(int selectedRow)
{
    QJsonArray games = savedGames_.find("Games").value().toArray();

    QJsonObject game               = games.at(selectedRow).toObject();
    QString date                   = game.find("Date").value().toString();
    QString fen                    = game.find("Fen").value().toString();
    int timeElapsed                = game.find("TimeElapsed").value().toInt();
    QString capturedPiecesPlayer   = game.find("CapturedPiecesPlayer").value().toString();
    QString capturedPiecesComputer = game.find("CapturedPiecesComputer").value().toString();
    int     kingPosInCheck         = game.find("KingPosInCheck").value().toInt();
    QString currentTurn            = game.find("CurrentTurn").value().toString();

    gameManager_.startNewGame(fen, [=](){
        gameManager_.loadGameCompleted(timeElapsed
                                     , kingPosInCheck
                                     , currentTurn
                                     , capturedPiecesPlayer
                                     , capturedPiecesComputer);
    });
}

