cmake_minimum_required(VERSION 3.15)
project(opencv_TTTide)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED COMPONENTS)
find_package(VTK REQUIRED)

add_subdirectory(eceuil_detection)
add_subdirectory(girouette)