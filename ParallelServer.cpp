//
// Created by maayan on 29/01/2020.
//

#include "ParallelServer.h"
#include "searchable.h"
#include "matrix.h"
#include "BFSAlgorithm.h"

ParallelServer::ParallelServer(){
    this->run=false;
}

void ParallelServer::setrun(bool run){
    this->run=run;
}
ParallelServer::~ParallelServer(){
    closeServer(this->socketfd);
}

int ParallelServer::openServer(int port, ClientHandler<string>* clientHandler){
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

    //this->_thread = new thread(getClient,socketfd,address,this);
    this->_thread=new thread(getClient,socketfd,address,this,clientHandler);

    return 1;
}

int ParallelServer::closeServer(int socketfd) {
    // tell thread it should stop
    this->run = false;
    this->_thread->join();
    delete _thread;
    close(socketfd); //closing the listening socket
    return 45;
}

void readFromClient( ClientHandler<string>* myClient,int client_socket,int socketfd,ParallelServer* server){

    myClient->handleClient(client_socket);

}


void getClient(int socketfd,sockaddr_in address,ParallelServer* server,ClientHandler<string>* clientHandler){
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
        else{
            //std::cout <<"client "+server->threadsList.size()<<" connected";
            server->threadsList.push_back(new thread(readFromClient,clientHandler, client_socket, socketfd,server));
        }

    }
}
