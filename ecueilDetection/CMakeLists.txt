add_executable(ecueilDetection ecueilDetection.cpp ecueilDetection.h ../ConnectionToHL/connectionToHL.cpp ../ConnectionToHL/connectionToHL.h main.cpp)


target_include_directories(ecueilDetection PRIVATE ${OpenCV_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS} )
target_link_directories(ecueilDetection PRIVATE ${OpenCV_INCLUDE_DIRS} ${VTK_LIBRARY_DIRS})
target_link_libraries(ecueilDetection opencv_core opencv_videoio opencv_highgui opencv_imgproc)