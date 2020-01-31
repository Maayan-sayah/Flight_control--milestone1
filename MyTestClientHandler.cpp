//
// Created by maayan on 18/01/2020.
//

#include <string>
#include <cstring>
#include <mutex>


#include "MyTestClientHandler.h"
#include "BFSAlgorithm.h"
#include "Solver.h"
#include "FileCachManager.h"
#include "objectAdapter.h"

#include "ParallelServer.h"
#include "searchable.h"
#include "matrix.h"
#include "BFSAlgorithm.h"
#include "AStarAlgorithm.h"

using namespace std;

string PORT="5400";
class NotSeccsedAccept: public exception{

};

//template<typename Problem, typename Solution, typename T>
MyTestClientHandler::MyTestClientHandler(CacheManager* cacheManager){
    this->cacheManager =cacheManager;
    this->solverOA = new objectAdapter<State<point>,string>(new BFSAlgorithm<State<point>,string>());
}

CacheManager* MyTestClientHandler:: getCach(){
    return this->cacheManager;
}

//template <typename  Problem,typename Solution,typename T>
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
//    vector<string> vectorOfString;
//    string findinCache="";
//    char buffer[1024] = {0};
//    int valread = read(socket, buffer, 1024);
//    while (strcmp(buffer,"end\r\n")!=0){
//        vectorOfString.push_back(buffer);
//        findinCache+=buffer;
//        memset(buffer,0,1024);
//        int valread = read(socket, buffer, 1024);
//    }

//    char* buffer[2000] = {0};
//    int valread = read(socket, buffer, 2000);
//    string strbuffer;
//
//
//    //char token[1024]={0};
//    char* token=strtok(buffer, "\n");
//    while (strcmp(token,"end\r")!=0){
//        //strcpy(token,strbuffer.c_str());
//        string temp=token;
//        vectorOfString.push_back(temp);
//        findinCache+=strbuffer;
//        token=strtok(NULL, "\n");
//    }

//
//    vector<string> vectorOfString;
//    char* buffer;
//   while(true){
//       read(socket, buffer,3000);
//       string line(buffer);
//       memset(buffer,0,3000);
//       if (!strcmp(line.c_str(), "end\r\n")) {
//           //GlobalShouldStop = true;
//           break;
//       }
//       vectorOfString.push_back(line);
//       findinCache+=line;
//   }


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
//    close(socket);
    //server->setrun(false);

}





