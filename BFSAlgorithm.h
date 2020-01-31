//
// Created by maayan on 25/01/2020.
//

#ifndef MILESTONE2_BFSALGORITHM_H
#define MILESTONE2_BFSALGORITHM_H

#include <queue>
#include "Searcher.h"
#include "BestAlgorithm.h"
using namespace std;
template <typename  Problem,typename Solution>
class BFSAlgorithm: public Searcher<Problem,Solution>{
    int nodesEvaluated=0;
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
        nodesEvaluated++;
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
                    nodesEvaluated++;
                    point temp = n->getCameFrom();
                    vector<point> solution;
                    solution.push_back(n->getCurrentstate());
                    //TODO find the problem
                    while (temp != ptt) {
                        solution.push_back(temp);
                        temp = returnCameFromPoint(temp,open);
                    }
                    return toSolution(fromPointToStateList(solution,searcable));
                }

                if (!(pointInQueue(*s,states))&&!(pointInVector(*s,open))){//not in queue and not in set
                    nodesEvaluated++;
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
            newS.setCost(searcable->getCost(t));
            direction+=newS.getCost();
            newS.setDirection(direction);
            listOfState.push_back(newS);
        }
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


#endif //MILESTONE2_BFSALGORITHM_H
