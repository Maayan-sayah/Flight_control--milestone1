//
// Created by maayan on 19/01/2020.
//

#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H

#include <string>
#include <vector>
#include "searchable.h"
using namespace std;
class Solver {
public:
    virtual string solve(searchable<State<point>>* problem)=0;
};

#endif //MILESTONE2_SOLVER_H
