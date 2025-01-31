/**
 * @class ImageMetaDataViewer
 * @brief Implementation of the ImageMetaDataViewer class for handling image processing tasks.
 *
 * This file contains the implementation of the ImageMetaDataViewer class, which includes loading images from a directory,
 * loading metadata for individual images, and managing messages related to image processing. It utilizes Qt's
 * asynchronous capabilities to perform non-blocking image loading and processing.
 *
 * @author Sivagopinathredd Vinta
 * @date  Creation date 2024-06-27
 */


#include "ImageMetaDataViewer.h"
#include <iostream>

#include <QImage>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

#include <thread>
#include <chrono>

ImageMetaDataViewer::ImageMetaDataViewer(QObject *parent)
    : QObject(parent)
{
}

void ImageMetaDataViewer::loadImages(const QString &directoryPath) {
    if (mLoading)
        return;
    mDirectoryPath = directoryPath;
    setLoading(true);

    auto start = std::chrono::high_resolution_clock::now();

    std::thread([this, start, directoryPath]() {

        // Simulate long-running operation
        std::this_thread::sleep_for(std::chrono::seconds(3));

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

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // with this block ensuring loading on this main thread
        // which ensures ui thread not blocking
        QMetaObject::invokeMethod(this, [=]() {
            setLoading(false);
        }, Qt::QueuedConnection);
    }).detach();
}

void ImageMetaDataViewer::setLoading(bool loading) {
    if (mLoading != loading) {
        mLoading = loading;
        emit loadingChanged();
    }
}

QString ImageMetaDataViewer::message() const {
    return mMessage;
}

QString ImageMetaDataViewer::loadMetadata(const QString &imageName) {
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

void ImageMetaDataViewer::updateMessage(const QString &newMessage) {
    if (mMessage != newMessage) {
        mMessage = newMessage;
        emit messageChanged();
    }
}

void ImageMetaDataViewer::onImageClicked(const QString &imageName) {
    QString metadataMessage = loadMetadata(imageName);
    updateMessage(metadataMessage);
}
