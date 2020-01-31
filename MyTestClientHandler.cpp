//
// Created by maayan on 18/01/2020.
//

#include <string>
#include <cstring>
#include <mutex>


#include "MyTestClientHandler.h"
#include "Solver.h"
#include "FileCachManager.h"
#include "objectAdapter.h"

#include "ParallelServer.h"
#include "searchable.h"
#include "matrix.h"

#include "AStarAlgorithm.h"

using namespace std;


class NotSeccsedAccept: public exception{

};


MyTestClientHandler::MyTestClientHandler(CacheManager* cacheManager){
    this->cacheManager =cacheManager;
    this->solverOA = new objectAdapter<State<point>,string>(new AStarAlgorithm<State<point>,string>());
}

CacheManager* MyTestClientHandler:: getCach(){
    return this->cacheManager;
}

void MyTestClientHandler::handleClient(int socket) {
    mutex mutex1;
    vector<string> vectorOfString;
    char problemline[1024]={0};
    int isread;
    bool boolread=true;
    string findinCache="";
    while(boolread){
        isread=read(socket, problemline, 1024);
        int j;
        if (isread<0){
            cerr<< "error"<<endl;
        }
        if ((strcmp(problemline,"end")==0)||(strcmp(problemline,"end\n")==0)||(strcmp(problemline,"end\r\n")==0)){
            boolread=false;
            break;
        }else{
            vectorOfString.push_back(problemline);
            findinCache+=problemline;
            memset(problemline,0,1024);
            isread=read(socket, problemline, 1024);
            if (isread==-1){
                cerr<< "error"<<endl;
            }else if((strcmp(problemline,"end")==0)||(strcmp(problemline,"end\n")==0)||(strcmp(problemline,"end\r\n")==0)) {
                boolread = false;
                break;
            }else{
                vectorOfString.push_back(problemline);
                findinCache+=problemline;
                memset(problemline,0,1024);
            }
        }

    }

    string ans;

    string startIndex=vectorOfString[vectorOfString.size() - 2];
    string goalIndex=vectorOfString[vectorOfString.size() - 1];
    vectorOfString.erase(vectorOfString.end());
    vectorOfString.erase(vectorOfString.end());
    hash<string> hasher;
    int hash = int(hasher(findinCache));
    searchable<State<point>>* searchable=new matrix(vectorOfString,startIndex,goalIndex);
    mutex1.lock();
    if (this->cacheManager->inCachManager(to_string(hash),findinCache)){
        ans=this->cacheManager->get(to_string(hash));
        mutex1.unlock();
    } else{
        mutex1.unlock();
        ans=this->solverOA->solve(searchable);
        mutex1.lock();
        this->cacheManager->insert(to_string(hash),findinCache);
        mutex1.unlock();
    }


    //writing back to client

    int is_sent = send(socket,ans.c_str(), ans.size(), 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"message sent to server" <<std::endl;
    }
}





