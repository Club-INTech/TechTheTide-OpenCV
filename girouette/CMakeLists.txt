cmake_minimum_required(VERSION 3.15)
project(girouette)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

add_executable(girouette main.cpp)

target_include_directories(girouette PRIVATE ${OpenCV_INCLUDE_DIRS} )
target_link_directories(girouette PRIVATE ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(girouette ${OpenCV_LIBS} opencv_aruco)