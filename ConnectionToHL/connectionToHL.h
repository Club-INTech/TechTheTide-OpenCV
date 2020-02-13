//
// Created by yasmine on 12/02/2020.
//
#include <iostream>
#include <array>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <csignal>
#include <unistd.h>

#ifndef OPENCV_TTTIDE_CONNECTIONTOHL_H
#define OPENCV_TTTIDE_CONNECTIONTOHL_H


class connectionToHL {
public:
    static bool connect();
    static void clientDisconnect();
    static bool send(const std::string& message);
    static bool read(std::string& receivedMessage);

};


#endif //OPENCV_TTTIDE_CONNECTIONTOHL_H
