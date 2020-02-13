#include "girouette.h"
#include "iostream"
#include "../ConnectionToHL/connectionToHL.h"
//
// Created by AznekEnimsay (yasmine) on 13/02/2020.
//

using namespace std;
using namespace cv;

int main(int args, char** argv) {

    string position = "o";
    int compteur = 0;
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
    compteur = 0;
    string config;
    int results;
    std::tie(results, config) = girouette::tagAruco();
    while (compteur < 10 && results != 0) {
        std::tie(results, config) = girouette::tagAruco();
        compteur += 1;
    }
    if (compteur == 10) {return results;}
    connectionToHL::send(config);
    connectionToHL::clientDisconnect();
    return results;
}
