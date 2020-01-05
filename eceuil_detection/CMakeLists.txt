cmake_minimum_required(VERSION 3.15)
project(eceuil_detection)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

add_executable(eceuil_detection main.cpp)

target_include_directories(eceuil_detection PRIVATE ${OpenCV_INCLUDE_DIRS} )
target_link_directories(eceuil_detection PRIVATE ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(eceuil_detection ${OpenCV_LIBS})
