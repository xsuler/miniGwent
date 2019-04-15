#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include"graphactor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    GraphActor GA;
    QQmlContext *ctx=engine.rootContext();
    ctx->setContextProperty("GA",&GA);
    ctx->setContextProperty("NA",&(GA.NA));
    GA.startGA();
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
