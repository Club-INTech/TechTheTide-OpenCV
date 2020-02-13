#include <iostream>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>
#include <array>
#include "../ConnectionToHL/connectionToHL.h"

//
// Created by yasmine on 28/01/2020.
//

#ifndef OPENCV_TTTIDE_ECUEILDETECTION_H
#define OPENCV_TTTIDE_ECUEILDETECTION_H


class ecueilDetection {
public:
    static std::tuple<int, std::vector<cv::Point2f>> cameraTraitement();
    static cv::String Configuration( std::vector<cv::Point2f> mc , const std::string& position);

};

#endif //OPENCV_TTTIDE_ECUEILDETECTION_H
