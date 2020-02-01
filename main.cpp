#include <iostream>
#include "cmake-build-debug/MyTestClientHandler.h"
#include "cmake-build-debug/ClientHandler.h"
#include "cmake-build-debug/ParallelServer.h"
#include "cmake-build-debug/Searcher.h"


#include "cmake-build-debug/FileCachManager.h"


using namespace std;
int main(int argc, char *argv[]) {
    int PORT=stoi(argv[1]);
    Server_side::Server* server1= new ParallelServer();
    CacheManager* cacheManager=new FileCachManager();

    ClientHandler<string>* clientHandler = new MyTestClientHandler(cacheManager);
    int  i=server1->openServer(PORT,clientHandler);

    while (true){
        this_thread::sleep_for(chrono::minutes(1));
    }
    return i;
}