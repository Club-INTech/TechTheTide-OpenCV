#include "opencv2/imgproc/imgproc.hpp"
#include <array>
#include "../ConnectionToHL/connectionToHL.h"
#include "ecueilDetection.h"

//
// Created by AznekEnimsay (yasmine) on 13/02/2020.
//

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    string position = "o";
    int compteur = 0;
    int results;
    vector<Point2f> mc;
    std::tie(results, mc) = ecueilDetection::cameraTraitement();
    while (compteur < 10 && results != 0) {
        std::tie(results, mc) = ecueilDetection::cameraTraitement();
        compteur += 1;
    }
    if (compteur == 10) {return results;}
    compteur = 0;
    connectionToHL::connect();
    connectionToHL::send(position);
    if ( position != "b" || position != "j") {
        while (compteur < 10 && (position != "b" || position != "j")) {
            connectionToHL::read(position);
            compteur += 1;
        }
    }
    else {
        position = "j"; // Default Position
    }
    string config = ecueilDetection::Configuration(mc , position);
    connectionToHL::send(config);
    connectionToHL::clientDisconnect();
    return results;
}