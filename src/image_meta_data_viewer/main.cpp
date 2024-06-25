#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ImageProcessor.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImageProcessor>("com.ImageProcessor", 1, 0, "ImageProcessor");

    QQmlApplicationEngine engine;
    ImageProcessor *processor = new ImageProcessor();
    engine.rootContext()->setContextProperty("imageProcessor", processor);
    QObject::connect(processor, &ImageProcessor::imageClicked, processor, &ImageProcessor::onImageClicked);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}
