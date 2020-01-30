//
// Created by maayan on 18/01/2020.
//

#ifndef MILESTONE2_SEARCHABLE_H
#define MILESTONE2_SEARCHABLE_H

#include <list>
#include "State.h"
#include "point.h"

template <typename T>
class searchable {
public:

    virtual T getGoalState()=0;
    virtual T getInitialState()=0;
    virtual std::list<T*> getAllPossibleState(point)=0;
    virtual void print()=0;
    virtual int getCost(T t)=0;
    virtual double getAvg()=0;

};


#endif //MILESTONE2_SEARCHABLE_H
