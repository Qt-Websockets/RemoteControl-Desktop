#include "echoclient.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

WebSocketClient::WebSocketClient(const QUrl &url, QObject *parent) :
    QObject(parent),
    m_url(url)
{
    qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketClient::closed);
    connect(&m_webSocket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
        [=](QAbstractSocket::SocketError error){ qDebug() << "Error establishing socket: " << error; });
    m_webSocket.open(QUrl(m_url));
}

void WebSocketClient::connectButtonClicked(QString username, QString computerName)
{
    m_webSocket.sendTextMessage(QString("{\"type\": \"connection\", \"content\": '{\"user\": \"%1\", \"computerName\": \"%2\"}'}").arg(username, computerName));
    emit messageRecieved("Registered.");
}

void WebSocketClient::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebSocketClient::onTextMessageReceived);
    emit messageRecieved(QString("Connected."));
}

void WebSocketClient::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
    if (message == QString("wake")) {
        qDebug() << "Command to wake recieved.";
        system("caffeinate -u -t 2");
    }
    emit messageRecieved(message);
//    m_webSocket.close();
}
