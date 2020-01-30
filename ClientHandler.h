//
// Created by maayan on 18/01/2020.
//

#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H

#include <string>
#include <vector>
#include "searchable.h"

using namespace std;
template <typename T>
class ClientHandler {

    public:
        //ClientHandler();
        virtual void handleClient(int socket)=0;
    //~ClientHandler();
};


#endif //MILESTONE2_CLIENTHANDLER_H
