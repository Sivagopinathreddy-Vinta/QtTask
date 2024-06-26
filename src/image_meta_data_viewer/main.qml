
// @brief Main QML interface for the application
// Filename: main.qml

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.ImageProcessor 1.0


ApplicationWindow {
    id:window
    visible: true
    width: 640
    height: 480

    ImageProcessor {
        id: imageProcessor
    }

    ListModel {
        id: imageListModel
    }

    BusyIndicator {
        anchors.centerIn: parent
        running: imageProcessor.loading
        visible: imageProcessor.loading
    }

    Component.onCompleted: {
        console.log("QML loaded successfully.");
    }

    RowLayout {
        id: rowLayout
        anchors.centerIn: parent

        TextField {
            id: directoryInput
            text: "C:/WorkSpace/DataBase"
            placeholderText: "Enter directory path"
            Layout.fillWidth: true
        }
        Button {
            text: "Load Images"
            onClicked: {
                var directory = directoryInput.text;
                rowLayout.visible = false;
                imageProcessor.loadImages(directory);

            }
        }
    }

    Row {
        anchors.fill: parent


        ListView {
            width: parent.width * 0.5
            height: parent.height
            model: imageListModel
            spacing: 10
            delegate: Image {
                source: modelData
                width: 100
                height: 100
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var imageName = modelData.substring(modelData.lastIndexOf("/") + 1);
                        imageProcessor.onImageClicked(imageName); // Call the onImageClicked slot
                    }
                }
            }
        }

        Text {
            id: messageText
            text: imageProcessor.message
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 20
        }
    }

    Connections {
        target: imageProcessor
        function onImagesLoaded(imagePaths) {
            imageListModel.clear(); // Clear existing items
            imagePaths.forEach(function(path) {
                imageListModel.append({"source": "file:///" + path.replace(/\\/g, "/")});
            });
        }
    }

    Button {
        text: "OK"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        onClicked: window.close()
    }
}

