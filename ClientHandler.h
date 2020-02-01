//
// Created by maayan on 18/01/2020.
//

#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H

#include <string>
#include <vector>
#include "searchable.h"
#include "CacheManager.h"

using namespace std;
template <typename T>
class ClientHandler {

    public:
    virtual CacheManager* getCach()=0;
    virtual void handleClient(int socket)=0;
    virtual ~ClientHandler(){

    }
};


#endif //MILESTONE2_CLIENTHANDLER_H
