#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include "communication/CommandCreator.h"
#include "communication/CommandHandlerI.h"


class CommandI;

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:
    ConnectionHandler(CommandHandlerI& handler);

public slots:
    void onConnect();
    void onDisconnect();
    void onError(QAbstractSocket::SocketError error);
    void onBinaryMessageReceived(const QByteArray& message);

signals:
    void connectionEstablished();
    void connectionDisconnected();
    void connectionError(QAbstractSocket::SocketError error);

public:
    void connect();
    void sendCommand(CommandI& cmd);

private:
    QWebSocket socket_;
    CommandCreator creator_;
    CommandHandlerI& handler_;
};

#endif // CONNECTIONHANDLER_H
