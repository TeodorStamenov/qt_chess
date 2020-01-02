#pragma once
#include <QObject>
#include <QProcess>
#include <QVariant>

class GameManager;

class EngineProcess : public QObject
{
    Q_OBJECT

public:
    EngineProcess(GameManager& manager);
    ~EngineProcess();

    void processStart();
    void processRequest(const std::string& fen);

signals:
    void moveReady(QVariant);

public slots:
    void processStarted();
    void processErr(QProcess::ProcessError error);
    void processResponse();
    void moveFinish(QVariant s);

private:
    void movePostpone(const QString r);

private:
    QProcess process_;
    GameManager& manager_;
};
