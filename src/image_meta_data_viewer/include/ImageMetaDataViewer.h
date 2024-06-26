/**
 * @class ImageMetaDataViewer
 * @brief Implementation of the ImageMetaDataViewer class for handling image processing tasks.
 *
 * This file contains the implementation of the ImageMetaDataViewer class, which includes loading images from a directory,
 * loading metadata for individual images, and managing messages related to image processing. It utilizes Qt's
 * asynchronous capabilities to perform non-blocking image loading and processing.
 *
 * @author Sivagopinathreddy Vinta
 * @date  Creation date 2024-06-27
 */

#pragma once

#include <QObject>

class ImageMetaDataViewer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)

public:
    /**
     * @brief Constructor for ImageMetaDataViewer.
     * @param parent The parent QObject, default is nullptr.
     */
    explicit ImageMetaDataViewer(QObject *parent = nullptr);

    /**
     * @brief Loads images from the specified directory path.
     * @param directoryPath The path of the directory from which to load images.
     */
    Q_INVOKABLE void loadImages(const QString &directoryPath);

    /**
     * @brief Getter for the current message.
     * @return The current message as a QString.
     */
    QString message() const;

    /**
     * @brief Loads metadata for the specified image name.
     * @param imageName The name of the image for which to load metadata.
     * @return A QString containing the metadata or an error message.
     */
    QString loadMetadata(const QString &imageName);

    /**
     * @brief Updates the current message.
     * @param newMessage The new message to set.
     */
    void updateMessage(const QString &newMessage);

    void setLoading(bool loading);
    bool isLoading() const { return mLoading; }

signals:
    void imagesLoaded(const QStringList &imagePaths);
    void imageClicked(const QString &imageName);
    void messageChanged();
    void loadingChanged();

public slots:
    void onImageClicked(const QString &imageName);


private:
    QString mMessage;
    QString mDirectoryPath;
    bool mLoading = false;
};

