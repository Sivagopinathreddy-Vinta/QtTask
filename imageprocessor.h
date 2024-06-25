#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>

class ImageProcessor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)

public:
    explicit ImageProcessor(QObject *parent = nullptr);
    Q_INVOKABLE void loadImages(const QString &directoryPath);
    QString message() const;
    QString loadMetadata(const QString &imageName);
    void updateMessage(const QString &newMessage);

signals:
    void imagesLoaded(const QStringList &imagePaths);
    void imageClicked(const QString &imageName);
    void messageChanged();

public slots:
    void onImageClicked(const QString &imageName);


private:
    QString m_message;
    QString m_directoryPath;
};

#endif // IMAGEPROCESSOR_H
