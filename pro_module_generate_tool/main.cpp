#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "work.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    Work w;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    QObject *qml = engine.rootObjects()[0];
    QObject::connect(qml, SIGNAL(startGen(QString, QString)), &w,
                     SLOT(OnStartGen(QString, QString)));

    return app.exec();
}
