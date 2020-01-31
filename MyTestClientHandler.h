//
// Created by maayan on 18/01/2020.
//

#ifndef MILESTONE2_MYTESTCLIENTHANDLER_H
#define MILESTONE2_MYTESTCLIENTHANDLER_H


#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "Searcher.h"

using namespace std;

class MyTestClientHandler: public ClientHandler<string>{
    CacheManager* cacheManager;
    Solver *solverOA;


public:
    void handleClient(int socket);
    CacheManager* getCach();
    MyTestClientHandler(CacheManager* cacheManager);
};


#endif //MILESTONE2_MYTESTCLIENTHANDLER_H
