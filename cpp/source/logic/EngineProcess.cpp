#include "EngineProcess.h"
#include "GameManager.h"
#include <QFuture>
#include <QtConcurrent>


namespace
{
    const char* const ENGINE_NAME = "stockfish";
}

EngineProcess::EngineProcess(GameManager& manager)
    : manager_(manager)
{
    QObject::connect(&process_, &QProcess::started
                    , this    , &EngineProcess::processStarted);

    QObject::connect(&process_, &QProcess::errorOccurred
                   , this     , &EngineProcess::processErr);

    QObject::connect(&process_, &QProcess::readyRead
                   , this     , &EngineProcess::processResponse);

    QObject::connect(this     , &EngineProcess::moveReady
                   , this     , &EngineProcess::moveFinish);
}

EngineProcess::~EngineProcess()
{
    process_.close();
    process_.waitForFinished();
}

void EngineProcess::processStart()
{
    process_.start(ENGINE_NAME);
    process_.waitForStarted();
}

void EngineProcess::processRequest(const std::string &fen)
{
    const auto command = "position fen " + fen + "\ngo \n";
    process_.write(command.c_str());
    process_.waitForReadyRead();
}

void EngineProcess::processResponse()
{
    QString response(process_.readAllStandardOutput());
    const int n = response.indexOf("bestmove");

    if (n != -1) {
        QStringRef r(&response, n+9, 4);
        QFuture<void> f = QtConcurrent::run(this, &EngineProcess::movePostpone, r.toString());
    }
}

void EngineProcess::movePostpone(const QString move)
{
    qDebug() << "Engine move: " << move;
    QThread::msleep(2000);
    emit moveReady(QVariant::fromValue(move));
}

void EngineProcess::moveFinish(QVariant s)
{
    manager_.engineMove(s.toString());
}

void EngineProcess::processStarted()
{
    qDebug() << "stockfish started";
}

void EngineProcess::processErr(QProcess::ProcessError error)
{
    qDebug() << "stockfish err: " << static_cast<int>(error);
}
