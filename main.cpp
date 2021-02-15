#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "worker.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<WorkerInterface>("Workers", 1, 0, "Worker");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    qDebug() << "Main thread : " << QThread::currentThreadId();

    return app.exec();
}
