add_executable(girouette main.cpp)

target_include_directories(girouette PRIVATE ${OpenCV_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})
target_link_directories(girouette PRIVATE ${OpenCV_INCLUDE_DIRS} ${VTK_LIBRARY_DIRS})
target_link_libraries(girouette opencv_core opencv_videoio opencv_highgui opencv_imgproc opencv_aruco opencv_calib3d)