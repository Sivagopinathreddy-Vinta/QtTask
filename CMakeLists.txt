cmake_minimum_required(VERSION 3.5)

project(QtTask VERSION 0.1 LANGUAGES CXX)

# ---------------------------------- Options --------------------------------- #
# Testing
option(UT_ENABLED "Enable building all tests" OFF)

# --------------------------------- Settings --------------------------------- #
# Set C++ standard on global level
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "RelWithDebInfo") 
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "" FORCE)

# Use folder hierarchy when generating projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ------------------------------- Dependencies ------------------------------- #
# Check if Qt5 is already found
find_package(Qt5 COMPONENTS Core Gui Qml Quick Concurrent QUIET)

# QT_QPA_PLATFORM_PLUGIN_PATH
# check for this path was set C:\Qt\5.15.14\msvc2019_64\plugins\platforms

if(Qt5_FOUND)
    message(STATUS "Qt5 found: ${Qt5_DIR}")
else()
    message(WARNING "Qt5 not found. Please install Qt5 or set Qt5_DIR/bin  in your PATH environment variables.")
endif()

# ---------------------------------- Targets --------------------------------- #
add_subdirectory(src)

if(UT_ENABLED)
	list(APPEND CMAKE_PREFIX_PATH "C:/WorkSpace/OFFICE/dev/customers/eb_assist_hil/build/generators")
	find_package(GTest REQUIRED)
	enable_testing()
	
    add_subdirectory(test)
endif()
