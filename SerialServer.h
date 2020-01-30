//
// Created by maayan on 16/01/2020.
//

#ifndef MILESTONE2_SERIALSERVER_H
#define MILESTONE2_SERIALSERVER_H


#include "Server.h"
#include "MyTestClientHandler.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <cstring>
#include <vector>

#include "SerialServer.h"
#include "MyTestClientHandler.h"
#include "searchable.h"
#include "matrix.h"

class SerialServer: public Server_side::Server {

    std::thread *_thread;
    int socketfd;

public:
    bool run;
    SerialServer();
    int openServer(int port, ClientHandler<string>* clientHandler);
    int closeServer(int socketfd);
    ~SerialServer();
    void setrun(bool run);
};

void readFromClient(ClientHandler<string>* myClient,int client_socket,int socketfd,SerialServer* server);
void getClient(int socketfd,sockaddr_in address,SerialServer* server);
#endif //MILESTONE2_SERIALSERVER_H

