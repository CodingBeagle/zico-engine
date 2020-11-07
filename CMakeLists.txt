# Specify minimum required version for CMake
cmake_minimum_required(VERSION 3.18)

# Project's name
# Will hereafter be stored in variable "PROJECT_NAME".
project(zico-engine)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output folder where the program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Adds an executable target to the build process.
add_executable(zico-engine ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Set linker options for zico-engine target.
# As the application is a graphical windows application, I set the ENTRY point to be WinMainCRTStartup, meaning WinMain is used as entry point.
target_link_options(zico-engine PUBLIC "/ENTRY:WinMainCRTStartup")