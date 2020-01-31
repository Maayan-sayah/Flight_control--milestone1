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

//template <typename  Problem,typename Solution,typename T>
class MyTestClientHandler: public ClientHandler<string>{
    CacheManager* cacheManager;
    Solver *solverOA;


public:
    void handleClient(int socket);
    CacheManager* getCach();
    //MyTestClientHandler(CacheManager<T> *cm1, Solver<Problem,Solution>* solver1 );

    MyTestClientHandler(CacheManager* cacheManager);
};


#endif //MILESTONE2_MYTESTCLIENTHANDLER_H
