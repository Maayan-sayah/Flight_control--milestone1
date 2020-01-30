//
// Created by maayan on 25/01/2020.
//

#ifndef MILESTONE2_BFSALGORITHM_H
#define MILESTONE2_BFSALGORITHM_H

#include <queue>
#include "Searcher.h"
#include "BestAlgorithm.h"
using namespace std;
template <typename Solution, typename  Problem>
class BFSAlgorithm: public Searcher<Solution, Problem>{
public:
    Solution Search(searchable<Problem> *searcable) {
        point ptt={-1,-1};
        point *p = new point(searcable->getInitialState().getCurrentstate());
        Problem *startState = new Problem(*p);
        startState->setCost(searcable->getCost(*startState));
        startState->setDirection(searcable->getCost(*startState));
        Problem goal = searcable->getGoalState();
        goal.setCost(searcable->getCost(goal));

        queue<Problem *> states; //a priority queue of states to be evaluated
        vector<Problem> open; // a set of states already evaluated
        states.push(startState);

        while (!states.empty()) {
            Problem* n = states.front();
            open.push_back(*n);
            states.pop();

            list<Problem*> successors=searcable->getAllPossibleState(n->getCurrentstate());
            for (Problem* s:successors){
                Problem *newState = new Problem(s->getCurrentstate(),
                                                searcable->getCost(s->getCurrentstate()), n->getCurrentstate(),
                                                searcable->getCost(s->getCurrentstate()) + n->getDirection());

                if (n->getCurrentstate() == goal.getCurrentstate()) {
                    point temp = n->getCameFrom();
                    vector<point> solution;
                    solution.push_back(n->getCurrentstate());
                    //TODO find the problem
                    while (temp != ptt) {
                        solution.push_back(temp);
                        temp = returnCameFromPoint(temp,open);
                    }
                    return fromPointToStateList(solution,searcable);
                }

                if (!(pointInQueue(*s,states))&&!(pointInVector(*s,open))){//not in queue and not in set
                    states.push(newState);

            }
            }
        }
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

    bool pointInQueue(Problem p, queue<Problem*> queue) {
        priority_queue<Problem> newqueue;
        while (!queue.empty()) {
            Problem *s = queue.front();
            newqueue.push(*s);
            queue.pop();
            if (s->getCurrentstate() == p.getCurrentstate()) {
                return true;
            }
        }
        return false;
    }
};


#endif //MILESTONE2_BFSALGORITHM_H
