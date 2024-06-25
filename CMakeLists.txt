cmake_minimum_required(VERSION 3.5)

project(Helsondt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if Qt5 is already found
find_package(Qt5 COMPONENTS Core Gui Qml Quick Concurrent QUIET)

# QT_QPA_PLATFORM_PLUGIN_PATH
# check for this path was set C:\Qt\5.15.14\msvc2019_64\plugins\platforms

if(Qt5_FOUND)
    message(STATUS "Qt5 found: ${Qt5_DIR}")
else()
    message(WARNING "Qt5 not found. Please install Qt5 or set Qt5_DIR in your environment variables.")
endif()

add_subdirectory(src)