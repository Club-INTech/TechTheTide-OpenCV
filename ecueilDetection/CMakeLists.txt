add_executable(eceuil_detection ../Communication/communication.cpp ../Communication/communication.h ../Communication/main.cpp ecueilDetection.cpp ecueilDetection.h)

target_include_directories(eceuil_detection PRIVATE ${OpenCV_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS} )
target_link_directories(eceuil_detection PRIVATE ${OpenCV_INCLUDE_DIRS} ${VTK_LIBRARY_DIRS})
target_link_libraries(eceuil_detection opencv_core opencv_videoio opencv_highgui opencv_imgproc)