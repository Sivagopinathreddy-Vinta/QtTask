project(test_ImageMetaDataViewer)
configure_file(${CMAKE_CURRENT_LIST_DIR}/test_ImageMetaDataViewer.h.in ${CMAKE_CURRENT_BINARY_DIR}/generated/test_ImageMetaDataViewer.h )

include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)

add_executable(${PROJECT_NAME}
     test_ImageMetaDataViewer.cpp
)

target_link_libraries(${PROJECT_NAME}
      GTest::gtest
      GTest::gmock_main
      Qt5::Core
      Qt5::Quick
      ImageMetaDataViewerLib
)


target_include_directories(${PROJECT_NAME} PRIVATE
    ${GTest_INCLUDE_DIRS}
)

gtest_add_tests(TARGET ${PROJECT_NAME})


set_target_properties(${PROJECT_NAME}
    PROPERTIES
        FOLDER "test/unitTests/image_meta_data_viewer" # folder name
)

