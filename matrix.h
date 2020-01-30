//
// Created by maayan on 19/01/2020.
//

#ifndef MILESTONE2_MATRIX_H
#define MILESTONE2_MATRIX_H


#include <string>
#include "searchable.h"
#include <vector>

using namespace std;

#include "point.h"

class matrix: public searchable<State<point>> {
    vector<vector<int>> matrixnum;
    point Pstart;
    point Pgoal;
    int row;
    int col;
    double avg;

public:
    void print();
    matrix(vector<string> stringvector,string startindex,string goalindex);
    void setmatrix(vector<vector<int>> newmatrix);
    State<point> getGoalState();
    State<point> getInitialState();
    std::list<State<point>*> getAllPossibleState(point current);
    void setPstart(point p);
    void setPgoal(point p);
    int getCost(State<point> p);
    double getAvg();
    const point &getPstart() const;
    const point &getPgoal() const;
    int getRow() const;
    int getCol() const;
    void calculateAVG();


};

#endif //MILESTONE2_MATRIX_H
