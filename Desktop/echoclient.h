#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(const QUrl &url, QObject *parent = Q_NULLPTR);

signals:
    void closed();
    void messageRecieved(QString message);

public slots:
    void connectButtonClicked(QString username, QString computerName);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
};

#endif // ECHOCLIENT_H
