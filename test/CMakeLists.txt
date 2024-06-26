project(test_ImageProcessor)

add_executable(${PROJECT_NAME}
     test_ImageProcessor.cpp
)

target_link_libraries(${PROJECT_NAME}
      GTest::gtest
      GTest::gmock_main
)


target_include_directories(${PROJECT_NAME} PRIVATE
    ${GTest_INCLUDE_DIRS}
)

gtest_add_tests(TARGET ${PROJECT_NAME})


set_target_properties(${PROJECT_NAME}
    PROPERTIES
        FOLDER "test/unitTests/image_meta_data_viewer" # folder name
)

