//
// Created by maayan on 22/01/2020.
//

#ifndef MILESTONE2_ASTARALGORITHM_H
#define MILESTONE2_ASTARALGORITHM_H
#include "Searcher.h"
//#include <unordered_set>
#include <list>
#include <string.h>
#include <map>
#include <iostream>
#include <queue>
#include <set>
#include <cmath>
#include "Searcher.h"
#include "State.h"
#include "point.h"
using namespace std;

template <typename Solution, typename  Problem>

class AStarAlgorithm: public Searcher<Solution,Problem> {
    struct CompareWayState {
        bool operator()(Problem *const &s1, Problem *const &s2) {
            return s1->getDirection()>s2->getDirection();
        }
    };
    int nodesEvaluated;
    //BackTrace<point>* back;
    double cost;

public:
    Solution Search(searchable<Problem> *searcable){
        point ptt = {-1, -1};
        Problem goal = searcable->getGoalState();
        goal.setCost(searcable->getCost(goal));
        point *p = new point(searcable->getInitialState().getCurrentstate());
        Problem* startState = new Problem(*p);
        startState->setCost(searcable->getCost(*startState));
        startState->setDirection(searcable->getCost(*startState)+calculateG(startState->getCurrentstate(),goal.getCurrentstate(),searcable));
        list<Problem*> closed;
        list<Problem*> open;
        open.push_back(startState);

//        point ptt = {-1, -1};
//        point *p = new point(searcable->getInitialState().getCurrentstate());
//        Problem *startState = new Problem(*p);
//        startState->setCost(searcable->getCost(*startState));
//        startState->setDirection(searcable->getCost(*startState));
//        Problem goal = searcable->getGoalState();
//        goal.setCost(searcable->getCost(goal));
//
//        priority_queue<Problem *, vector<Problem *>, CompareWayState> open; //a priority queue of states to be evaluated
//        vector<Problem> closed; // a set of states already evaluated
//        open.push(startState);

        while(!open.empty()){
            float bigestCost = INFINITY;
            Problem *n;
            for (Problem *x : open) {
                if(x->getCost() + x->getDirection() < bigestCost)
                {
                    bigestCost = x->getCost() + x->getDirection();// this->allState[&x].first;
                    n = x;

                }
            }
            closed.push_back(n);
            open.remove(n);
            if (goal.getCurrentstate()==n->getCurrentstate()){
                point temp = n->getCameFrom();
                vector<point> solution;
                solution.push_back(n->getCurrentstate());
                while (temp != ptt) {
                    solution.push_back(temp);
                    temp = returnCameFromPoint(temp,closed);
                }
                return fromPointToStateList(solution,searcable);
            }
            list<Problem*> successors = searcable->getAllPossibleState(n->getCurrentstate());
            for (Problem *s:successors) {

                if (inList(*s, closed)) {
                    continue;
                }
                s->setCost(s->getCost()+ searcable->getCost(s->getCurrentstate()));

                if ((!inList(*s,open))||((inList(*s,open))&&(s->getCost()+s->getDirection()<n->getCost()))){

                    Problem *temp = new Problem(*n);
                    s->setCameFrom(temp->getCurrentstate());
                    s->setCost(n->getCost()+ s->getCost());
                    s->setDirection(abs((goal.getCurrentstate().first - s->getCurrentstate().first) * searcable->getAvg()) +
                    abs((goal.getCurrentstate().second -  s->getCurrentstate().second) * searcable->getAvg()));
                    if ((inList(*s, open))) {
                        open.remove(s);
                    }
                    open.push_back(s);
                }
            }
            }

    }
    point returnCameFromPoint(point find, list<Problem*> vec) {
        for (Problem* t:vec) {
            if (t->getCurrentstate() == find) {
                return t->getCameFrom();
            }
        }
        return {-1, -1};
    }



    double calculateG(point p1,point p2, searchable<Problem>* searchable){
        return (abs((p2.first-p1.first)*searchable->getAvg())+abs((p2.second-p1.second)*searchable->getAvg()));
    }

    vector<Problem> fromPointToStateList(vector<point> vec, searchable<Problem> *searcable){
        vector<Problem> listOfState;
        int direction=0;
        for (point t:vec) {
            Problem newS=Problem(t);
            listOfState.push_back(newS);
            direction+=searcable->getCost(newS);
        }
        int size=listOfState.size();
        listOfState[listOfState.size()-1].setDirection(direction);
        return listOfState;
    }

    bool inList(Problem p,list<Problem*> list){
        for (Problem* temp:list){
            if (temp->getCurrentstate()==p.getCurrentstate()){
                return true;
            }
        }
        return false;
    }

    bool pointInQueue(Problem p, priority_queue<Problem *, vector<Problem *>, CompareWayState> queue) {
        priority_queue<Problem> newqueue;
        while (!queue.empty()) {
            Problem *s = queue.top();
            newqueue.push(*s);
            queue.pop();
            if (s->getCurrentstate() == p.getCurrentstate()) {
                return true;
            }
        }
        return false;
    }

    bool pointInVector(Problem p, vector<Problem*> vec) {
        for (Problem t:vec) {
            if (t.getCurrentstate() == p.getCurrentstate()) {
                return true;
            }
        }
        return false;
    }

    point returnCameFromPoint(point find, vector<Problem> vec) {
        for (Problem t:vec) {
            if (t.getCurrentstate() == find) {
                return t.getCameFrom();
            }
        }
        return {-1, -1};
    }
    vector<Problem> fromPointToStateList(list<point> vec, searchable<Problem> *searcable){
        vector<Problem> listOfState;
        int direction=0;
        for (point t:vec) {
            Problem newS=Problem(t);
            newS.setCost(searcable->getCost(newS));
            listOfState.push_back(newS);
            direction+=newS.getCost();
        }
        int size=listOfState.size();
        listOfState[listOfState.size()-1].setDirection(direction);
        return listOfState;
    }
};



//string Search(searchable<Problem>* toSearch){
//    list<Problem> open;
//    std::map<point, Problem> costHash;
//    list<Problem> backTraceList;
//    Problem goal = toSearch->getGoalState();
//
//    int goalI = toSearch->getGoalState().getCurrentstate().first;
//    int goalJ = toSearch->getGoalState().getCurrentstate().second;
//
//    open.push_back(toSearch->getInitialState());
//    //open.push_back(toSearch->getInitialState());
//    costHash.insert(pair<point, Problem>(toSearch->getInitialState().getCurrentstate(), toSearch->getInitialState()));
//
//    while(!open.empty()){
//        Problem state = open.front();
//        open.pop_front();
//        double stateCost = costHash.find(state.getCurrentstate())->second.getCost();
//        //this->nodesEvaluated++;
//
//        if(state==goal){
//            //todo return back
//            vector<point> p;
//            int direction;
//            printf("goal");
////                while(state.getCameFrom()!=NULL){
////
////                }
//            //return this->back->backTrace(state, toSearch, cost);
//        }
//
//        list<Problem*> succerssors = toSearch->getAllPossibleState(&state);
//
//        while (!succerssors.empty()){
//            Problem temp = *succerssors.front();
//            succerssors.pop_front();
//
//            //string nameTemp = temp->getState();
//            //char* divideTemp = const_cast<char *>(nameTemp.c_str());
//            int tempI = temp.getCurrentstate().first;
//            int tempJ = temp.getCurrentstate().second;
//
//            double h = abs(tempI - goalI) + abs(tempJ - goalJ);
//            double g = temp.getCost() + stateCost;
//            double newCost = h + g;
//
//            //int x= ;
//            if(costHash.count(temp.getCurrentstate())){
//                double preCost = costHash.find(temp.getCurrentstate())->second.getCost();
//                if (newCost < preCost){
//                    temp.setCameFrom(&state);
//                    temp.setCost(newCost);
//                    //temp->setDirection();
//                    costHash.insert(pair<point, Problem>(temp.getCurrentstate(), temp));
//                }
//            }
//            else {
//                temp.setCameFrom(&state);
//                temp.setCost(newCost);
//                open.push_back(temp);
//                costHash.insert(pair<point, Problem>(temp.getCurrentstate(), temp));
//            }
//        }
//    }
//    printf("No route found.");
//    return "-1";
//}
#endif //MILESTONE2_ASTARALGORITHM_H
