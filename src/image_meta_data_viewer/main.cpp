#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ImageMetaDataViewer.h"
#include <memory>  

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImageMetaDataViewer>("com.ImageProcessor", 1, 0, "ImageProcessor");

    QQmlApplicationEngine engine;
    std::unique_ptr<ImageMetaDataViewer> processor = std::make_unique<ImageMetaDataViewer>();
    engine.rootContext()->setContextProperty("imageProcessor", processor.get());

    QObject::connect(processor.get(), &ImageMetaDataViewer::imageClicked,
                     processor.get(), &ImageMetaDataViewer::onImageClicked); 

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}
