//
// Created by maayan on 18/01/2020.
//

#include <string>
#include <cstring>


#include "MyTestClientHandler.h"
#include "BFSAlgorithm.h"
#include "Solver.h"
#include "FileCachManager.h"
#include "objectAdapter.h"

#include "ParallelServer.h"
#include "searchable.h"
#include "matrix.h"
#include "BFSAlgorithm.h"

using namespace std;

string PORT="5400";
class NotSeccsedAccept: public exception{

};

//template<typename Problem, typename Solution, typename T>
MyTestClientHandler::MyTestClientHandler(Searcher<State<point>,string>* searcher){
    this->cacheManager = new FileCachManager();
    this->solverOA = new objectAdapter<State<point>,string>(searcher);
}

//template <typename  Problem,typename Solution,typename T>
void MyTestClientHandler::handleClient(int socket) {

    vector<string> vectorOfString;
    string findinCache="";
    char buffer[1024] = {0};
    int valread = read(socket, buffer, 1024);
    while (strcmp(buffer,"end\r\n")!=0){
        vectorOfString.push_back(buffer);
        findinCache+=buffer;
        memset(buffer,0,1024);
        int valread = read(socket, buffer, 1024);
    }
    string ans;

    string startIndex=vectorOfString[vectorOfString.size() - 2];
    string goalIndex=vectorOfString[vectorOfString.size() - 1];
    vectorOfString.erase(vectorOfString.end());
    vectorOfString.erase(vectorOfString.end());
    hash<string> hasher;
    int hash = int(hasher(findinCache));
    searchable<State<point>>* searchable=new matrix(vectorOfString,startIndex,goalIndex);
    if (this->cacheManager->inCachManager(to_string(hash),findinCache)){
        ans=this->cacheManager->get(to_string(hash));
    } else{
        ans=this->solverOA->solve(searchable);
        this->cacheManager->insert(to_string(hash),findinCache);
    }

    //writing back to client

    int is_sent = send(socket,ans.c_str(), ans.size(), 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"message sent to server" <<std::endl;
    }
    close(socket);
    //server->setrun(false);

}





