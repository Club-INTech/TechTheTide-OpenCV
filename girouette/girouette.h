#include <opencv2/core.hpp>
#include <vector>
#include "opencv2/aruco/dictionary.hpp"
#include "opencv2/aruco.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include <opencv2/calib3d.hpp>
#include "cmath"

//
// Created by yasmine on 28/01/2020.
//

#ifndef OPENCV_TTTIDE_GIROUETTE_H
#define OPENCV_TTTIDE_GIROUETTE_H


class girouette {
public :
    static cv::Vec3f rotationMatrixToEulerAngles(cv::Mat &R);
    static std::tuple<int, std::string> tagAruco();

};

cv::Matx33d cameraMatrix = cv::Matx33d(.0767696485099054e+02, 0., 6.3074175237948407e+02, 0., 8.0767696485099054e+02,
                                   3.8551547885624814e+02, 0., 0., 1.);
cv::Matx14d distCoeffs = cv::Matx14d (0., 9.0756263737609579, 2.9472807904506051, 2.6490685322879028); //Parameters of the camera (OpenCV calibration)

#endif //OPENCV_TTTIDE_GIROUETTE_H
