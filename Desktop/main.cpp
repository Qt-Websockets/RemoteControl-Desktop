#include "mainwidget.h"
#include "echoclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    EchoClient client(QUrl(QStringLiteral("ws://localhost:4567/echo")));
    QObject::connect(&client, &EchoClient::closed, &a, &QApplication::quit);

    return a.exec();
}
