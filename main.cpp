#include <iostream>
#include "cmake-build-debug/MyTestClientHandler.h"
#include "cmake-build-debug/ClientHandler.h"
#include "cmake-build-debug/ParallelServer.h"
#include "cmake-build-debug/Searcher.h"
#include "cmake-build-debug/BestAlgorithm.h"

#include "cmake-build-debug/FileCachManager.h"
#include "cmake-build-debug/objectAdapter.h"

using namespace std;
int main() {
    int PORT=5400;
    //MyTestClientHandler clientHandler();
    Server_side::Server* server1= new ParallelServer;
    Searcher<State<point>,string>* searcher=new BestAlgorithm<State<point>,string>;
    ClientHandler<string>* clientHandler = new MyTestClientHandler(searcher);

    int  i=server1->openServer(PORT,clientHandler);

    while (true){
        this_thread::sleep_for(chrono::minutes(1));
    }
    return 0;
}