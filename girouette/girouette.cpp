#include "girouette.h"


using namespace cv;
using  namespace std;
using namespace aruco;

/* @author yam
 * creation : 13/12/2019
 * last modification : 05/01/2020
 */

// Calculates rotation matrix to euler angles

Vec3f girouette::rotationMatrixToEulerAngles(Mat &R) {
    double sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );

    bool singular = sy < 1e-6; // If

    double x, y, z;
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

tuple<int, string> girouette::tagAruco() {

    int results = 0;
    std::string config = "0";
    cv::VideoCapture inputVideo;
    inputVideo.open(1);

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
            Vec3f EulerMatrix = girouette::rotationMatrixToEulerAngles(R); // Searching for the rotation of the aruco tag
            for (int i = 0; i < 3; i++) {
                EulerMatrix[i] = (EulerMatrix[i] * 180) / M_PI; // Conversion in degree
            }
            if (EulerMatrix[1] < 0) { config = "N"; } // EulerMatrix[1] = y coordinate
            else { config = "S"; }
        }
        if (config == "0") {
            results = 1;
            break;

        }
        else {
            inputVideo.release();
            break;
        }
    }
    return std::make_tuple(results, config);
}
