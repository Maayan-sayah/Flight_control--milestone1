//
// Created by maayan on 26/01/2020.
//

#ifndef MILESTONE2_OBJECTADAPTER_H
#define MILESTONE2_OBJECTADAPTER_H


#include "Solver.h"
#include "BFSAlgorithm.h"

template <typename  Problem,typename Solution>

class objectAdapter: public Solver{
private:
    Searcher<Problem,Solution>* searcher;
public:
    objectAdapter(Searcher<State<point>,string>* searcher) {
        this->searcher=searcher;
    }
    string solve(searchable<State<point>>* problem){
        return this->searcher->Search(problem);
    }


};


#endif //MILESTONE2_OBJECTADAPTER_H
