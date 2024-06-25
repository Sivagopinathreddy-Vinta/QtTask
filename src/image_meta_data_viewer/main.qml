import QtQuick 2.12
import QtQuick.Controls 2.12
import com.example 1.0

ApplicationWindow {
    id:window
    visible: true
    width: 640 // Increased width to accommodate split view
    height: 480

    ImageProcessor {
        id: imageProcessor
    }

    Component.onCompleted: {
        console.log("QML loaded successfully.");
        imageProcessor.loadImages("C:/WorkSpace/DataBase");
    }

    ListModel {
        id: imageListModel
    }

    Row { // Splitting the view into two sections
        anchors.fill: parent

        ListView {
            width: parent.width * 0.5 // Takes half the width
            height: parent.height
            model: imageListModel
            spacing: 10
            delegate: Image {
                source: modelData
                width: 100
                height: 100
                MouseArea {
                    anchors.fill: parent
                   // onClicked: {
                   //     messageText.text = "Hi " + modelData.substring(modelData.lastIndexOf("/") + 1);
                   // }
                    onClicked: {
                        var imageName = modelData.substring(modelData.lastIndexOf("/") + 1);
                        imageProcessor.onImageClicked(imageName); // Call the onImageClicked slot
                    }
                }
            }
        }

        Text {
            id: messageText
            text: imageProcessor.message // Bind to the message property
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
