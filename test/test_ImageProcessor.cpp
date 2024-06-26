#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ImageProcessor.h" // Assuming this is the header file where the class is defined

// Test fixture class
class ImageProcessorTest : public ::testing::Test {
protected:
    ImageProcessor* processor;

    void SetUp() override {
        processor = new ImageProcessor();
    }

    void TearDown() override {
        delete processor;
    }
};

// Test case for verifying mLoading is true when loading starts
TEST_F(ImageProcessorTest, LoadingStateTrueOnStart) {
    processor->startLoading();
    ASSERT_TRUE(processor->mLoading);
}

// Test case for verifying mLoading is false after loading is complete
TEST_F(ImageProcessorTest, LoadingStateFalseAfterLoad) {
    processor->startLoading();
    processor->finishLoading();
    ASSERT_FALSE(processor->mLoading);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
