//
// Created by maayan on 16/01/2020.
//

#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include "MyTestClientHandler.h"

using namespace std;
namespace Server_side{
    class Server {
    public:
        virtual int openServer(int port, ClientHandler<string>* clientHandler)=0;
        virtual int closeServer(int socketfd)=0;
    };
}



#endif //MILESTONE2_SERVER_H
