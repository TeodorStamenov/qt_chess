#include "ConnectionHandler.h"
#include "utils/Logger.h"
#include "communication/Buffer.h"
#include "communication/commands/SrvHandshakeCmd.h"
#include "communication/commands/ClHandshakeCmd.h"

namespace
{
    const QString LOG_FILE = "Commands";

    void log(const QString& msg)
    {
        Logger::instance().log(LOG_FILE, msg);
    }
}

ConnectionHandler::ConnectionHandler(CommandHandlerI& handler)
    : handler_(handler)
{
    QObject::connect(&socket_, &QWebSocket::connected
                     , this, &ConnectionHandler::onConnect);

    QObject::connect(&socket_, &QWebSocket::disconnected
                     , this, &ConnectionHandler::onDisconnect);

    QObject::connect(&socket_, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error)
                     , this, &ConnectionHandler::onError);

    QObject::connect(&socket_, &QWebSocket::binaryMessageReceived
                     , this, &ConnectionHandler::onBinaryMessageReceived);
}

void ConnectionHandler::onConnect()
{
    emit connectionEstablished();
}

void ConnectionHandler::onDisconnect()
{
    emit connectionDisconnected();
}

void ConnectionHandler::onError(QAbstractSocket::SocketError error)
{
    emit connectionError(error);
}

void ConnectionHandler::onBinaryMessageReceived(const QByteArray& message)
{
    Buffer buf(static_cast<size_t>(message.size()));
    buf.fromByteArr(message);

    CommandPtr cmd = creator_.createCommand(buf);
    cmd->deserialize(buf);

    log(cmd->name());

    cmd->handle(handler_);
}

void ConnectionHandler::connect()
{
    socket_.open(QUrl(QStringLiteral("ws://localhost:1337")));
}

void ConnectionHandler::sendCommand(CommandI& cmd)
{
    log(cmd.name());
    Buffer buf(cmd.getSize());
    cmd.serialize(buf);
    socket_.sendBinaryMessage(buf.toByteArr().begin());
}



