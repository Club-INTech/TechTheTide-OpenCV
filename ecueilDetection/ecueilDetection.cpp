#include "ecueilDetection.h"


/* @author AznekEnimsay (yasmine)
 * creation : 05/12/2019
 * last modification : 13/12/2019 */


using namespace cv;
using namespace std;


tuple<int, vector<Point2f>> ecueilDetection::cameraTraitement() {
    VideoCapture cap(1); //capture the video from web cam

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return std::make_tuple(1, std::vector<Point2f>());
    }

    // Read the green intervals in code_greenDetection.txt


    std::string filename = "code_greenDetection.txt";

    std::fstream fs;

    fs.open(filename);

    int iLowH;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    fs >> iLowH;
    int iHighH;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    fs >> iHighH;
    int iLowS;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    fs >> iLowS;
    int iHighS;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    fs >> iHighS;
    int iLowV;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    fs >> iLowV;
    int iHighV;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    fs >> iHighV;



    // Camera treatment

    Mat imgOriginal1;

    bool bSuccess = cap.read(imgOriginal1); // read a new frame from video

    if (!bSuccess) //if not success, break loop
    {
        cout << "Cannot read a frame from video stream" << endl;
        return std::make_tuple(1, std::vector<Point2f>());
    }

    /* Made by Willy */

    cv::Rect roi(imgOriginal1.cols / 4, imgOriginal1.rows / 4, imgOriginal1.cols / 2, imgOriginal1.rows / 2);
    cv::Mat imgOriginal = imgOriginal1(roi); /* End of what Willy has done  */

    // Pb correction méca caméra? ROI qui change de l'autre côté ?

    Mat imgHSV;

    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    Mat imgThresholded;

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV),
            imgThresholded); //Threshold the image

    //morphological opening (remove small objects from the foreground)

    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    //morphological closing (fill small holes in the foreground)
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(30, 5))); //Separate the cups

    //imshow("Thresholded Image", imgThresholded); waitKey(1);
    // show the thresholded image
    //imshow("Original", imgOriginal); waitKey(1);
    // show the original image


    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

// detect edges using canny
    Canny(imgThresholded, canny_output, 50, 150, 3);

// find contours
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

// get the moments
    vector<Moments> mu(contours.size());
    for (int i = 0; i < contours.size(); i++) { mu[i] = moments(contours[i], false); }

// get the centroid of figures.
    vector<Point2f> mc(contours.size());
    for (int i = 0; i < contours.size(); i++) {
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
    }
    return std::make_tuple(0, mc);

}

String ecueilDetection::Configuration( vector<Point2f> mc , const std::string& position) {

    while(true) {

        String config = "RRRRR";

// get the distance between each centroids and returns the configurations
        if (position == "b") {
            double dist1;
            double dist2;
            double dist3;
            if (mc.size() != 6) {
                int results;
                std::tie(results, mc) = cameraTraitement(); }
            else {
                if (fabs(mc[2].y - mc[0].y) == fabs(mc[2].y - mc[0].y)) {
                    dist1 = fabs(mc[2].y - mc[0].y);
                    if (dist1 <= 75 && dist1 >= 65) {
                        config = "RVRVV";
                        return config;
                    }
                }
                if (fabs(mc[4].y - mc[2].y) == fabs(mc[4].y - mc[2].y)) {
                    dist2 = fabs(mc[4].y - mc[2].y);
                    if (dist2 <= 72 && dist2 >= 62) {
                        config = "RVVRV";
                        return config;
                    }
                }
                if (fabs(mc[5].y - mc[0].y) == fabs(mc[5].y - mc[0].y)) {
                    dist3 = fabs(mc[5].y - mc[0].y);
                    if (dist3 <= 70 && dist3 >= 60) {
                        config = "RRVVV";
                        return config;
                    }
                }
            }
        }
        if (position == "j") {
            double dist1;
            if (mc.size() != 4) {
                int results;
                std::tie(results, mc) = cameraTraitement(); }
            else {
                if (fabs(mc[2].y - mc[0].y) == fabs(mc[2].y - mc[0].y)) {
                    dist1 = fabs(mc[2].y - mc[0].y);
                    if (dist1 <= 115 && dist1 >= 105) {
                        config = "VRRVR";
                        return config;

                    } else if (dist1 <= 80 && dist1 >= 70) {
                        config = "VRVRR";
                        return config;

                    } else if (dist1 <= 40 && dist1 >= 30) {
                        config = "VVRRR";
                        return config;

                    }
                }
            }
        }


 /* FOR TESTS ONLY
  *
  *
    // draw contours
                Mat drawing(canny_output.size(), CV_8UC3, Scalar(255, 255, 255));
                for (int i = 0; i < contours.size(); i++) {
                    Scalar color = Scalar(167, 151, 0); // B G R values
                    drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
                    circle(drawing, mc[i], 4, color, -1, 8, 0);
                }
    // show the resultant image
                namedWindow("Contours", WINDOW_NORMAL);
                imshow("Contours", drawing);

                if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                {
                    cout << "esc key is pressed by user" << endl;
                    break;
    } */

        cout<<"Error : no pattern found"<<endl;
        return config;

    }
}
