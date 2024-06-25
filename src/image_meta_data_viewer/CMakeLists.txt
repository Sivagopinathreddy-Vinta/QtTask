project(ImageMetaDataViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Concurrent)

set(image_meta_data_viewer_includes
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ImageProcessor.h
    )

set(image_meta_data_viewer_sources
       main.cpp
       ImageProcessor.cpp
    )

set(image_meta_data_viewer_resources
       qml.qrc
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
        Qt5::Concurrent
    )

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        FOLDER "image_meta_data_viewer" # folder name
    )

#include(GNUInstallDirs)
#install(TARGETS ${PROJECT_NAME}
#    BUNDLE DESTINATION .
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

