//
// Created by AznekEnimsay (yasmine) on 12/02/2020.
//

#include "connectionToHL.h"


int clientSocket = -1;
uint16_t serverPort = 17566;



/**
 * Sets up a TCP server waiting for connection from robot's high level
 * @param serverAddress Address to which the client will connect to
 * @param serverPort Port the client will connect to
 * @return Socket ID of high level if connection was successful
 */

bool connectionToHL::connect()
{
    // Setup the server socket
    int serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);

    if(!serverSocket)
    {
        std::cerr << "Could not open server socket" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        errno = 0;      // Reset errno after error processing
        return(false);
    }


    // Configure the server socket
    sockaddr_in serverSocketDescriptor{};
    serverSocketDescriptor.sin_family = AF_INET;

    serverSocketDescriptor.sin_port = htons(serverPort);
    serverSocketDescriptor.sin_addr.s_addr = htonl(INADDR_ANY);

    // Set socket options to force address and port reuse if possible
    // Avoids "Address already in use" errors when binding
    int trueOption = 1;
    if(setsockopt(serverSocket,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&trueOption,sizeof(trueOption)) < 0)
    {
        std::cerr << "Could not set socket options" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        errno = 0;
        return(false);
    }


    // Bind the socket to the configured address and port
    if(bind(serverSocket,reinterpret_cast<sockaddr*>(&serverSocketDescriptor),sizeof(serverSocketDescriptor)) < 0)
    {
        std::cerr << "Could not bind socket to address :" << serverPort << std::endl;
        std::cerr << strerror(errno) << std::endl;
        errno = 0;
        return(false);
    }


    // Start listening for inbound connections
    uint16_t connectionBacklog = 1;
    if(listen(serverSocket,connectionBacklog) < 0)
    {
        std::cerr << "Could not start listening on socket" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        errno = 0;
        return(false);
    }


    // If there is an inbound connection, accept the connection and retrieve the client socket
    std::cout << "Waiting for connection on address 0.0.0.0:" << serverPort << std::endl;
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // If connection failed, try until a connection is established
    while(clientSocket < 0)
    {
        std::cerr << "Could not connect to client" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        std::cerr << "Trying again..." << std::endl;
        errno = 0;
        clientSocket = accept(serverSocket, nullptr, nullptr);
    }

    std::cout << "ConnectionToHL successful !" << std::endl;

    shutdown(serverSocket,SHUT_RDWR);
    close(serverSocket);

    return(true);
}

void connectionToHL::clientDisconnect()
{
    std::cerr << "Client disconnected !" << std::endl;
    std::cerr << strerror(errno) << std::endl;
    errno = 0;

    shutdown(clientSocket,SHUT_RDWR);
    close(clientSocket);
    clientSocket = -1;
}


bool connectionToHL::send(const std::string& message)
{
    if(clientSocket == -1)
    {
        return(false);
    }

    int16_t sentBytes = ::write(clientSocket,message.c_str(),message.size());

    // If the pipe is broken or the write failed, disconnect properly
    if(signal(SIGPIPE,SIG_IGN) == SIG_ERR || sentBytes < 0)
    {
        clientDisconnect();
        return(false);
    }

    return(true);
}

/** Début du traitement d'image pour détecter la configuration**/

bool connectionToHL::read(std::string& receivedMessage) {

    receivedMessage.clear();

    if (clientSocket < 0) {
        return (false);
    }
    static constexpr uint16_t bufferSize = 100;
    char receptionBuffer[bufferSize];

    // Try to receive data
    ssize_t receivedLength = ::recv(clientSocket, receptionBuffer, bufferSize, 0);

    // If reception failed ...
    if (receivedLength < 0) {
        // ... check if it was expected (Non blocking socket that would block) or if there was an unexpected error
        if (!(errno & (EWOULDBLOCK | EAGAIN))) {
            // If it was unexpected, print an error message
            std::cerr << "Error while trying to read from address :" << serverPort << std::endl;
            std::cerr << strerror(errno) << std::endl;
        }
        errno = 0;
        return (false);
    }
    else if (receivedLength == 0) // Or, if we received a zero-length message, consider that the client disconnected
    {
        errno = ECONNRESET;
        clientDisconnect();
        return (false);
    }

    // Copy received data to the output string
    receivedMessage.assign(receptionBuffer, (uint16_t) receivedLength);
    return true;
}

