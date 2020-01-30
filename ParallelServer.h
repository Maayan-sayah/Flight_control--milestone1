//
// Created by maayan on 29/01/2020.
//

#ifndef MILESTONE2_PARALLELSERVER_H
#define MILESTONE2_PARALLELSERVER_H

#include "ClientHandler.h"
#include "Server.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <cstring>
#include <vector>



class ParallelServer :public Server_side::Server {

std::thread *_thread;


int socketfd;

public:
bool run;
    ParallelServer();
int openServer(int port, ClientHandler<string>* clientHandler);
int closeServer(int socketfd);
~ParallelServer();
void setrun(bool run);

    vector<std::thread*> threadsList;
};

void readFromClient(ClientHandler<string>* myClient,int client_socket,int socketfd,ParallelServer* server);
void getClient(int socketfd,sockaddr_in address,ParallelServer* server,ClientHandler<string>* clientHandler);
#endif //MILESTONE2_PARALLELSERVER_H
