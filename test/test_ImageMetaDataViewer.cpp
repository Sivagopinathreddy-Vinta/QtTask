#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ImageMetaDataViewer.h"
#include <test_ImageMetaDataViewer.h>

class ImageMetaDataViewerTest : public ::testing::Test 
{
protected:

    void SetUp() override {
        testDirectoryPath = "C:/WorkSpace/DataBase";
        viewer = new ImageMetaDataViewer();
    }

    void TearDown() override {
        delete viewer;
        viewer = nullptr;
    }

    ImageMetaDataViewer* viewer;
    QString testDirectoryPath;
};


TEST_F(ImageMetaDataViewerTest, TestLoadMetadata)
{
    std::string filename = TEST_RESOURCE_PATH_H;
    filename += "sample_image.jpg";
    QString imageName = QString::fromStdString(filename);
    QString expectedMessage = "Image: sample_image.jpg\nField of View: 60.0\nAzimuth: 120.0\nElevation: 30.0";

    // Load metadata
    QString actualMessage = viewer->loadMetadata(imageName);

    // Assert that the loaded metadata matches the expected message
    ASSERT_EQ(actualMessage, expectedMessage);
}