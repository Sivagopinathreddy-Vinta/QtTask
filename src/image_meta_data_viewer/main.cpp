#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ImageMetaDataViewer.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImageMetaDataViewer>("com.ImageProcessor", 1, 0, "ImageProcessor");

    QQmlApplicationEngine engine;
    ImageMetaDataViewer *processor = new ImageMetaDataViewer();
    engine.rootContext()->setContextProperty("imageProcessor", processor);
    QObject::connect(processor, &ImageMetaDataViewer::imageClicked, processor, &ImageMetaDataViewer::onImageClicked);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}
