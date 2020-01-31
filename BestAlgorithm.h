//
// Created by maayan on 21/01/2020.
//

#ifndef MILESTONE2_BESTALGORITHM_H
#define MILESTONE2_BESTALGORITHM_H

#include <iostream>
#include <queue>
#include <set>
#include "Searcher.h"
#include "State.h"
#include "point.h"

using namespace std;

template <typename  Problem,typename Solution>

class BestAlgorithm :public Searcher<Problem,Solution> {
    struct CompareWayState {
        bool operator()(Problem *const &s1, Problem *const &s2) {
            return s1->getDirection()>s2->getDirection();
        }
    };
    int nodesEvaluated=0;

public:
    Solution Search(searchable<Problem>* searcable) {
        point ptt = {-1, -1};
        point *p = new point(searcable->getInitialState().getCurrentstate());
        Problem *startState = new Problem(*p);
        startState->setCost(searcable->getCost(*startState));
        startState->setDirection(searcable->getCost(*startState));
        Problem goal = searcable->getGoalState();
        goal.setCost(searcable->getCost(goal));

        priority_queue<Problem *, vector<Problem *>, CompareWayState> open; //a priority queue of states to be evaluated
        vector<Problem> closed; // a set of states already evaluated
        open.push(startState);
        nodesEvaluated++;
        while (!open.empty()) {
            Problem *n = open.top();
            closed.push_back(*n);
            open.pop();
            if (n->getCurrentstate() == goal.getCurrentstate()) {
                point temp = n->getCameFrom();
                vector<point> solution;
                solution.push_back(n->getCurrentstate());
                while (temp != ptt) {
                    solution.push_back(temp);
                    temp = returnCameFromPoint(temp,closed);
                }
                return toSolution(fromPointToStateList(solution,searcable));
            } else {
                list<Problem *> successors = searcable->getAllPossibleState(n->getCurrentstate());
                for (Problem *s:successors) {

                    Problem *newState = new Problem(s->getCurrentstate(),
                                                    searcable->getCost(s->getCurrentstate()), n->getCurrentstate(),
                                                    searcable->getCost(s->getCurrentstate()) + n->getDirection());
                    if ((n->getCameFrom() != ptt) && (n->getCameFrom() == s->getCurrentstate())) {

                    } else {
                        if (!(pointInQueue(*s, open))) {//not in queue
                            if (!pointInVector(*s,closed)){
                                nodesEvaluated++;
                            }

                            open.push(newState);
                        } else {
                            priority_queue<Problem *, vector<Problem *>, CompareWayState> tempOpen;
                            Problem *temp;
                            while (!open.empty()) {
                                temp = open.top();
                                open.pop();
                                if (temp->getCurrentstate() == s->getCurrentstate()) {

                                    if((temp->getDirection()>newState->getDirection())){
                                        temp->setCost(s->getDirection());
                                        point camefrom = s->getCameFrom();
                                        temp->setCameFrom(camefrom);
                                        open.push(temp);
                                        break;
                                    }
                                    else {
                                        open.push(temp);
                                        while (!tempOpen.empty()) {
                                            temp = tempOpen.top();
                                            tempOpen.pop();
                                            open.push(temp);
                                        }
                                        break;
                                    }
                                } else {
                                    tempOpen.push(temp);
                                    //open.pop();
                                }
                            }
                            while (!tempOpen.empty()) {
                                temp = tempOpen.top();
                                tempOpen.pop();
                                open.push(temp);
                            }
                        }
                    }
                }
            }
        }
    }


    vector<Problem> fromPointToStateList(vector<point> vec, searchable<Problem> *searcable){
        vector<Problem> listOfState;
        int direction=0;
        for (point t:vec) {
            Problem newS=Problem(t);
            newS.setCost(searcable->getCost(t));
            direction+=newS.getCost();
            newS.setDirection(direction);
            listOfState.push_back(newS);
        }
        return listOfState;
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

    bool pointInVector(Problem p, vector<Problem> vec) {
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

    string toSolution(vector<Problem> vec){
        string solution="";
        int i;
        int x1=vec[vec.size()-1].getCurrentstate().first;
        int y1=vec[vec.size()-1].getCurrentstate().second;
        int dir=0;
        for (i=vec.size()-1;i!=-1;i--){
            int x2=vec[i].getCurrentstate().first;
            int y2=vec[i].getCurrentstate().second;
            dir+=vec[i].getCost();
            if ((x1-x2)==1){
                solution+="Left ("+to_string(dir)+") ,";
            } else if((y1-y2)==1){
                solution+="Up ("+to_string(dir)+") ,";
            }
            else if ((x2-x1)==1){
                solution+="Right ("+to_string(dir)+") ,";
            }
            else if((y2-y1)==1){
                solution+="Down ("+to_string(dir)+") ,";
            }
            x1=x2;
            y1=y2;
        }
        solution+="\n"+to_string(nodesEvaluated)+"\n";
        return solution;
    }
};




#endif //MILESTONE2_BESTALGORITHM_H
