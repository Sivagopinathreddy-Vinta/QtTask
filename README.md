# ImageMetaDataViewer Application

This application is a simple image processing tool built using Qt.
It allows users to interact with images in getting meta data for the image, facilitated by the `ImageProcessor` class.

## Overview

The application is structured around Qt's QML and C++ integration, 
allowing for a responsive and intuitive UI. The `ImageProcessor` class is exposed to QML,
enabling direct interaction with images through the UI.


# Running the Application

**Important:** <span style="color:red">add `QT_DIR\bin` folder to environment path.</span>

You can view application in action directly `\files\application_testing.mp4`

Provide in `\files\ImageMetaDataViewer.exe` to run application 
for database `\app_setup\data_base` follow this structure place image file and json file with meta information and with same name 
dont use nested directories.

Once the Application runs it asks for database give this folder and enter once you all images loaded
you click on any image to get metadata of particular image written in json file.

# Bulding the Application
## Prerequisites

Before building the application, ensure you have the following installed:
- Qt 5.15.14 or any QT 5
- CMake 3.10 or later
- A compatible C++ compiler (GCC for Linux, MSVC for Windows)

## Building the Application with CMake GUI

1. **Open CMake GUI**: Start CMake GUI and set the source code directory to the location of your project's `CMakeLists.txt` file. Set the build directory to where you want the compiled binaries to be placed.

2. **Configure the Project**: Click on the "Configure" button. You will be prompted to select a generator for the project. Choose the appropriate generator for your development environment (e.g., "Visual Studio 16 2019" for Windows). Click "Finish" to start the configuration process. If there are any configuration issues, resolve them as prompted by CMake GUI.

3. **Select Build Options**: Once configuration is complete, you can optionally select build options or modify paths to dependencies. For this project, ensure Qt paths are correctly set if they are not automatically found.

4. **Generate Build Files**: Click on the "Generate" button to create the build system files for your selected generator.

5. **Build the Project**: After generation, you can build the project using your IDE or by clicking on the "Open Project" button in CMake GUI, which opens the project in your default IDE.

## Running the Application

After building, run the generated executable. On the first run, the application will display a UI for interacting with images.

## Troubleshooting

- **Qt Not Found**: Ensure that Qt is correctly installed and that the `CMAKE_PREFIX_PATH` environment variable is set to the Qt installation path.
- **Build Errors**: Verify that all prerequisites are installed and that the CMake configuration matches your development environment.
