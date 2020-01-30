//
// Created by maayan on 16/01/2020.
//
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


SerialServer::SerialServer(){
this->run=false;
}

void SerialServer::setrun(bool run){
    this->run=run;
}
SerialServer::~SerialServer(){
    closeServer(this->socketfd);
}
int SerialServer::openServer(int port, ClientHandler<string>* clientHandler){
//create socket
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }
    this->setrun(true);

    this->_thread = new thread(getClient,socketfd,address,this);

    return 1;
}

int SerialServer::closeServer(int socketfd) {
    // tell thread it should stop
    this->run = false;
    this->_thread->join();
    delete _thread;
    close(socketfd); //closing the listening socket
    return 45;
}

void readFromClient(ClientHandler<string>* myClient,int client_socket,int socketfd,SerialServer* server){

    vector<string> vectorOfString;

    //server->setrun(true);
    //while (server->run) {
        char buffer[1024] = {0};
        int valread = read(client_socket, buffer, 1024);
        while (strcmp(buffer,"end\r\n")!=0){
            vectorOfString.push_back(buffer);
            memset(buffer,0,1024);
            int valread = read(client_socket, buffer, 1024);
        }
        //todo read more twe line index start and end


    string startIndex=vectorOfString[vectorOfString.size() - 2];
    string goalIndex=vectorOfString[vectorOfString.size() - 1];
    vectorOfString.erase(vectorOfString.end());
    vectorOfString.erase(vectorOfString.end());
//    searchable<State<point>>* searchable=new matrix(vectorOfString,startIndex,goalIndex);
//


}

void getClient(int socketfd,sockaddr_in address,SerialServer* server){
    while (server->run) {
        //making socket listen to the port
        //todo time out
        if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
            std::cerr << "Error during listening command" << std::endl;
        } else {
            std::cout << "Server is now listening ..." << std::endl;
        }

        // accepting a client
        int client_socket = accept(socketfd, (struct sockaddr *) &address,
                                   (socklen_t *) &address);

        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
        }
        //ClientHandler *myClient = new MyTestClientHandler();
        //readFromClient(myClient, client_socket, socketfd, server);
    }
}
