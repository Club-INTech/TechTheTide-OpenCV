#include <opencv2/core.hpp>
#include <vector>
#include "opencv2/aruco/dictionary.hpp"
#include "opencv2/aruco.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include <opencv2/calib3d.hpp>
#include "cmath"



using namespace cv;
using  namespace std;
using namespace aruco;

/* @author yam
 * creation : 13/12/2019
 * last modification : 05/01/2020
 */

// Calculates rotation matrix to euler angles

Vec3f rotationMatrixToEulerAngles(Mat &R)
{
    float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );

    bool singular = sy < 1e-6; // If

    float x, y, z;
    if (!singular)
    {
        x = atan2(R.at<double>(2,1) , R.at<double>(2,2));
        y = atan2(-R.at<double>(2,0), sy);
        z = atan2(R.at<double>(1,0), R.at<double>(0,0));
    }
    else
    {
        x = atan2(-R.at<double>(1,2), R.at<double>(1,1));
        y = atan2(-R.at<double>(2,0), sy);
        z = 0;
    }
    return Vec3f(x, y, z);



}

int tagAruco() {

    array<char, 1> config = {{'O'}};
    cv::VideoCapture inputVideo;
    inputVideo.open(1);
    cv::Matx33d cameraMatrix = Matx33d(.0767696485099054e+02, 0., 6.3074175237948407e+02, 0., 8.0767696485099054e+02,
                                       3.8551547885624814e+02, 0., 0., 1.);
    cv::Mat distCoeffs = Mat(0., 9.0756263737609579e+00, 2.9472807904506051e+00, 2.6490685322879028e+00); //Parameters of the camera (OpenCV calibration)
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    while (inputVideo.grab()) {
        cv::Mat image, imageCopy;
        inputVideo.retrieve(image);
        image.copyTo(imageCopy);
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids); //searching for the 17th tag of the dictionary
        std::vector<cv::Vec3d> rvecs, tvecs;
        if (ids[0] == 17) {
            cv::aruco::estimatePoseSingleMarkers(corners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);
            Mat R;
            Rodrigues(rvecs, R);
            Vec3f EulerMatrix = rotationMatrixToEulerAngles(R); // Searching for the rotation of the aruco tag
            for (int i = 0; i < 3; i++) {
                EulerMatrix[i] = (EulerMatrix[i] * 180) / M_PI; // Conversion in degree
            }
            if (EulerMatrix[1] < 0) { config[0] = 'N'; } // EulerMatrix[1] = y coordinate
            else { config[0] = 'S'; }
        }
        if (config[0] != '0') {
            inputVideo.release();
            break;
        }
    }
    cout << config[0] << endl;
    return config[0];
}

int main(int args, char** argv) {
    return tagAruco();
}