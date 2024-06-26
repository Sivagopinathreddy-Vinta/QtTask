project(ImageMetaDataViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Quick)

set(image_meta_data_viewer_includes
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ImageMetaDataViewer.h
    )

set(image_processor_lib_sources
    ImageMetaDataViewer.cpp
)

set(image_meta_data_viewer_sources
       main.cpp
    )

set(image_meta_data_viewer_resources
       qml.qrc
    )

# Add library target for Gtest
add_library(${PROJECT_NAME}Lib
    ${image_processor_lib_sources}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ImageMetaDataViewer.h
)

set_target_properties(${PROJECT_NAME}Lib PROPERTIES
    AUTOMOC ON
)

target_include_directories(${PROJECT_NAME}Lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}Lib PUBLIC
    Qt5::Core
    Qt5::Quick
)

add_executable(${PROJECT_NAME}
    ${image_meta_data_viewer_sources}
    ${image_meta_data_viewer_includes}
    ${image_meta_data_viewer_resources}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt5::Core
        Qt5::Quick
        ${PROJECT_NAME}Lib
    )
set_target_properties(${PROJECT_NAME}Lib
    PROPERTIES
        FOLDER "image_meta_data_viewer" # folder name
    )


set_target_properties(${PROJECT_NAME}
    PROPERTIES
        FOLDER "image_meta_data_viewer" # folder name
    )

