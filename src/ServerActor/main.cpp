#include <QCoreApplication>
#include"tsserver.h"
#include"databaseactor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DatabaseActor::createTable();
    TSserver server;
    server.startServer(QHostAddress::LocalHost,3000);

    return a.exec();
}
