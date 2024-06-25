#include "ImageProcessor.h"

#include <QImage>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include <QtConcurrent>

ImageProcessor::ImageProcessor(QObject *parent)
    : QObject(parent)
{
}

void ImageProcessor::loadImages(const QString &directoryPath) {
    m_directoryPath = directoryPath;
    QtConcurrent::run([=]() {
        QDir dir(m_directoryPath);
        QStringList imageFiles = dir.entryList(QStringList() << "*.jpg", QDir::Files);
        QStringList imagePaths;
        for (const QString &file : imageFiles) {
            QString fullPath = dir.absoluteFilePath(file);
            imagePaths << fullPath;
            qDebug() << "Found image:" << fullPath; // Debugging
        }
        if (!imagePaths.isEmpty()) {
            qDebug() << "Emitting imagesLoaded with" << imagePaths.size() << "images";
            emit imagesLoaded(imagePaths);
        } else {
            qDebug() << "No images found in directory:" << m_directoryPath;
            //std::cout<< "No images found in directory:" << m_directoryPath
        }
    });
}

QString ImageProcessor::message() const {
    return m_message;
}

QString ImageProcessor::loadMetadata(const QString &imageName) {
    QString jsonFilePath = m_directoryPath + "/" + imageName;
    jsonFilePath.replace(".jpg", ".json");

    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return "Failed to open metadata file for " + imageName;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(fileData));
    if (!doc.isObject()) {
        return "Invalid JSON metadata for " + imageName;
    }

    QJsonObject jsonObj = doc.object();
    QString filename = jsonObj.value("filename").toString();
    double fieldOfView = jsonObj.value("fieldOfView").toDouble();
    double azimuth = jsonObj.value("azimuth").toDouble();
    double elevation = jsonObj.value("elevation").toDouble();

    return QString("Image: %1\nField of View: %2\nAzimuth: %3\nElevation: %4")
        .arg(filename)
        .arg(fieldOfView)
        .arg(azimuth)
        .arg(elevation);
}

void ImageProcessor::updateMessage(const QString &newMessage) {
    if (m_message != newMessage) {
        m_message = newMessage;
        emit messageChanged();
    }
}

void ImageProcessor::onImageClicked(const QString &imageName) {
    QString metadataMessage = loadMetadata(imageName);
    updateMessage(metadataMessage);
}
