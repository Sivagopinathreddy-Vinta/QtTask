/**
 * @class ImageProcessor
 * @brief Implementation of the ImageProcessor class for handling image processing tasks.
 *
 * This file contains the implementation of the ImageProcessor class, which includes loading images from a directory,
 * loading metadata for individual images, and managing messages related to image processing. It utilizes Qt's
 * asynchronous capabilities to perform non-blocking image loading and processing.
 *
 * @author Sivagopinathredd Vinta
 * @date  Creation date 2024-06-27
 */


#include "ImageProcessor.h"
#include <iostream>

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
    mDirectoryPath = directoryPath;
    QtConcurrent::run([=]() {
        QDir dir(mDirectoryPath);
        QStringList imageFiles = dir.entryList(QStringList() << "*.jpg", QDir::Files);
        QStringList imagePaths;
        for (const QString &file : imageFiles) {
            QString fullPath = dir.absoluteFilePath(file);
            imagePaths << fullPath;
        }
        if (!imagePaths.isEmpty()) {
            emit imagesLoaded(imagePaths);
        } else {
            std::cout << "No images found in directory: " << mDirectoryPath.toStdString() << std::endl;
        }
    });
}

QString ImageProcessor::message() const {
    return mMessage;
}

QString ImageProcessor::loadMetadata(const QString &imageName) {
    QString jsonFilePath = mDirectoryPath + "/" + imageName;
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
    if (mMessage != newMessage) {
        mMessage = newMessage;
        emit messageChanged();
    }
}

void ImageProcessor::onImageClicked(const QString &imageName) {
    QString metadataMessage = loadMetadata(imageName);
    updateMessage(metadataMessage);
}
