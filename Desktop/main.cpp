#include "mainwidget.h"
#include "echoclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    WebSocketClient client(QUrl(QStringLiteral("ws://localhost:4567/desktop")));
    QObject::connect(&client, &WebSocketClient::closed, &a, &QApplication::quit);
    QObject::connect(&client, &WebSocketClient::messageRecieved, &w, &MainWidget::messageRecieved);
    QObject::connect(&w, &MainWidget::connectButtonClicked, &client, &WebSocketClient::connectButtonClicked);

    return a.exec();
}
