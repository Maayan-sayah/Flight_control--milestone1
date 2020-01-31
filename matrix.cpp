//
// Created by maayan on 19/01/2020.
//

#include <iostream>
#include "matrix.h"
#include "Searcher.h"
#include "point.h"

using namespace std;



matrix::matrix(vector<string> stringvector,string startindex,string goalindex) {
    int i;
    vector<vector<int>> newmatrix;
    string num="";
    vector<string> :: iterator it=stringvector.begin();
    for(it;it!=stringvector.end();it++){
        vector<int> rowvector;
        string temp=*it;

        temp=temp.substr(0,temp.length()-1);
        for (i=0;i<temp.length();i++){
            while ((temp[i]!=',')&&(i<temp.length())){
                if (temp[i]!=' '){
                    num+=temp[i];
                }
                i++;
            }
            rowvector.push_back(stoi(num));
            num="";
        }
        newmatrix.push_back(rowvector);

    }
    this->row=newmatrix.size();
    this->col=newmatrix[0].size();

    this->matrixnum=newmatrix;

    int x;
    int y;
    i=0;
    while (startindex[i]!=','){
        if (startindex[i]!=' '){
            num+=startindex[i];
        }
        i++;
    }
    x=stoi(num);
    num="";
    i++;
    while (i<startindex.length()){
        if (startindex[i]!=' '){
            num+=startindex[i];
        }
        i++;
    }
    y=stoi(num);
    point pstart={.first =x, .second=y};
    this->setPstart(pstart);
    x=0;
    y=0;
    num="";
    i=0;
    while (goalindex[i]!=','){
        if (goalindex[i]!=' '){
            num+=goalindex[i];
        }
        i++;
    }
    x=stoi(num);
    num="";
    i++;
    while (i<goalindex.length()){
        if (goalindex[i]!=' '){
            num+=goalindex[i];
        }
        i++;
    }
    y=stoi(num);
    point pgoal={x,y};
    this->setPgoal(pgoal);

    calculateAVG();
}

//typedef std::pair<int, int> point;
State<point> matrix::getGoalState(){
    State<point>* s=new State<point>(this->Pgoal);
    return *s;
}

State<point> matrix::getInitialState(){
    State<point>* s=new State<point>(this->Pstart);
    return *s;
}


std::list<State<point>*> matrix::getAllPossibleState(point current){
    list<State<point>*> possibleState;
    //State<point>* camefrom= new State<point>(currState->getCurrentstate());
    if (current.first!=0){
        if (this->getCost(point{current.first-1,current.second})!=-1){
            point nei = {current.first-1,current.second};
            State<point>* state=new State<point>(nei);
            state->setCameFrom(current);
            state->setCost(this->getCost(nei));
            possibleState.push_back(state);
        }
    }

    if (current.first!=this->col-1){
        if(this->getCost(point{current.first+1,current.second})!=-1){
            point nei = {current.first+1,current.second};
            State<point>* state=new State<point>(nei);
            state->setCameFrom(current);
            state->setCost(this->getCost(nei));
            possibleState.push_back(state);
        }
    }
    if (current.second!=0){
        if (this->getCost(point{current.first,current.second-1})!=-1){
            point nei = {current.first,current.second-1};
            State<point>* state=new State<point>(nei);
            state->setCameFrom(current);
            state->setCost(this->getCost(nei));
            possibleState.push_back(state);
        }
    }

    if (current.second!=this->row-1) {
        if (this->getCost(point{current.first, current.second + 1}) != -1) {
            point nei = {current.first, current.second + 1};
            State<point> *state = new State<point>(nei);
            state->setCameFrom(current);
            state->setCost(this->getCost(nei));
            possibleState.push_back(state);
        }
    }
    return possibleState;
}

const point &matrix::getPstart() const {
    return Pstart;
}

const point &matrix::getPgoal() const {
    return Pgoal;
}

int matrix::getRow() const {
    return row;
}

int matrix::getCol() const {
    return col;
}

void matrix::calculateAVG(){
    int i,j;
    double avg=0;
    for (i=0;i<col;i++){
        for (j=0;j<row;j++){
            point p={j,i};
            avg+=this->getCost(p);
        }
    }
    avg=avg/((col-1)*(row-1));
    this->avg=avg;
}

int matrix::getCost(State<point> t) {
    //return this->matrixnum[t.getCurrentstate()->first][t.getCurrentstate()->second];

    //todo replace x y if the solution is not correct
    return this->matrixnum[t.getCurrentstate().second][t.getCurrentstate().first];
}

void matrix::setPstart(point p){
    this->Pstart=p;
}

void matrix::setPgoal(point p){
    this->Pgoal=p;
}
void matrix::print(){
    cout<<this->row<<" row"<<endl;
    cout<<this->col<<" col"<<endl;
    cout<<this->Pstart.first<<" , "<<this->Pstart.second<<" pstart"<<endl;
    cout<<this->Pgoal.first<<" , "<<this->Pgoal.second<<" pGOAL"<<endl;
}

double matrix::getAvg() {
    return avg;
}

#include "BestAlgorithm.h"
#include "BFSAlgorithm.h"
#include "AStarAlgorithm.h"

//int main(){
//    std::vector<string> temp= {
//            "8,2,8,6,8,2,12,2,4,1,9,9,5,12,1,1,1,2,7,3,1,6,9,3,9,7,7,9,5,6,4,5,1,6,-1,1,7\r\n",
//            "4,12,2,3,2,5,2,1,12,2,4,5,4,3,3,4,12,2,3,9,6,9,1,6,7,7,5,8,7,2,-1,3,2,5,-1,9,2\r\n",
//            "1, 5, 8, 9, 2, 1, 2, 4, 7, 8, 2, 9, 8, 4, 2, 2,12, 8, 8, 2, 3, 3, 1, 5,12,-1, 2, 7, 1, 4,-1,-1,-1, 2,-1, 5, 6\r\n",
//            "8, 6, 2, 4,12, 8, 9, 9, 7, 1, 2, 8, 8, 2, 4, 2, 1, 7, 6, 8, 3,-1, 8, 1, 8, 6, 1, 3, 3, 2, 7, 3, 4, 2, 9,12, 2\r\n",
//            "7, 6, 2,12, 7, 8, 1,-1, 5, 8, 8, 1, 1, 5, 8, 9, 9, 1, 8, 5, 1, 8, 4, 5, 4, 5, 8, 7, 6, 6, 8, 2, 2, 8, 8, 8, 8\r\n",
//            "9, 3, 2, 3, 5,12,-1, 9, 2, 8, 3, 8, 2,12,12, 7, 1, 8, 4, 2,12, 5, 4, 7, 4, 4, 6,12, 9, 2, 3, 5,12, 2, 2, 3, 5\r\n",
//            "12, 5, 1, 7, 5,12, 6, 6, 6, 5, 8, 9, 4, 3, 9, 2,12, 4, 9, 5, 3,12, 3, 9, 3, 4,-1, 8, 5, 2,12, 5, 2, 3, 7, 6,-1\r\n",
//            " 1,12, 2, 9, 9, 1, 2, 2,-1, 2, 6,12, 1,12,12, 2, 7, 5, 2, 7, 7, 6, 9, 2, 3, 2, 4, 9,-1, 5, 7,-1, 9, 8, 6, 3, 4\r\n",
//            "12, 2, 1, 2, 6,12, 2, 6,-1,-1, 3, 9, 9, 8, 3, 7, 4, 3, 4, 5,-1, 9, 3, 5,12, 2, 3,-1,12, 2, 2, 2, 7, 8,-1,12, 2\r\n",
//            " 7, 4, 8, 2, 8, 7,-1, 3,-1, 2,-1, 7, 9, 6, 7, 6, 1,12, 6, 2, 5, 8, 1, 2, 8, 3, 2,12, 7,12, 1, 2, 6, 9, 7, 3, 8\r\n",
//            " 6, 2, 4, 7, 7,12, 8, 2, 1, 6, 2, 6, 4, 6, 6, 7, 5, 5, 8, 2,12, 2, 6, 8,12, 8,12, 9, 9, 2, 2, 2, 9, 6, 5, 4, 2\r\n",
//            " 7, 2, 9, 4, 7, 4, 5, 8, 2, 2, 4, 3, 6, 1, 4, 7, 4, 9,-1, 5,12, 3, 4, 9, 7,12, 3, 5, 2, 9, 7, 2,-1, 5,12, 7, 1\r\n",
//            " 6, 6, 8, 2,12, 4,-1, 4,-1, 2, 9, 6, 5, 7, 2, 4, 9,12, 4, 9, 2, 9, 2, 6, 7, 1,12, 5, 6, 6, 5,12, 4, 5, 7, 6, 8\r\n",
//            " 3, 9, 1, 4, 8, 2,-1, 2,-1, 7, 8, 3, 6, 6, 9, 4, 6,-1, 4,-1, 1, 4, 5, 9, 2, 2, 1, 9, 3, 7, 2, 1,12, 5, 6,-1, 9\r\n",
//            "12, 8, 9, 1,12, 7, 2,12, 9,12,12, 1, 9, 3, 7, 5, 9, 3, 8, 6, 6, 7, 1, 1, 5, 6, 2, 7, 2, 3, 4, 9, 9, 9,12, 2, 8\r\n",
//            "12, 2, 8, 5,-1, 2, 5, 8, 7, 2, 5, 1, 3, 2, 4, 3, 9, 5, 9, 7, 7, 2,-1, 2, 8, 4, 1, 5, 9, 6, 2, 4, 2, 9, 1,-1, 2\r\n",
//            " 4, 4, 5,12, 2, 5, 2, 3, 2, 2, 2, 4, 5, 3,12, 9, 3, 6, 2, 9, 9, 1, 4, 3, 2,12, 3, 1, 8, 6, 7, 4, 6, 7, 5, 1, 8\r\n",
//            " 4,-1, 9, 7, 5, 5, 3,12, 8, 3, 3, 9, 5, 6, 1,12, 7, 4, 9, 9, 5, 9, 8, 9, 9, 1, 6, 9, 7, 5, 3, 5, 4, 6, 3, 2, 1\r\n",
//            " 9, 2, 1, 5, 1, 3, 8, 2, 1, 2, 5, 2, 9, 9, 3, 4, 2, 2, 2,12, 7, 2,12, 3, 7, 2, 8, 9, 2, 1, 2, 2, 2, 3, 4,12, 3\r\n",
//            " 6, 6, 1,-1,12, 7, 1, 5, 2, 3, 5, 8,12, 7, 3, 2, 6, 8, 5, 1,12, 2, 6, 6, 8, 2, 7,-1, 2, 7, 9, 5, 5, 7, 1, 5, 4\r\n",
//            " 3, 6, 4,12, 7, 8, 2, 9, 8, 3, 4, 3, 8, 7, 6, 6, 2, 7, 9, 6, 6, 2, 2, 6, 5, 9, 2, 3, 3, 3,12, 7,12, 6, 7, 2, 9\r\n",
//            "12, 1, 2,-1, 7, 2, 5,12, 2, 8, 4, 7, 8, 7, 7, 5, 2, 5, 7, 4, 2, 4, 3,12, 6, 8, 5, 2, 1, 4, 9, 2, 1, 4, 2, 2, 2\r\n",
//            "12, 4, 9,12, 9,12, 9,12, 7, 9, 2, 1, 6, 5, 3, 2, 6, 4, 7, 9,12, 4, 4, 9, 8, 1, 7, 8, 2, 2, 9, 3, 8, 5, 3, 7, 6\r\n",
//            " 7, 4, 6, 2, 7, 7, 8, 6, 8, 9, 1, 2, 9, 3, 4, 9, 2, 8,12, 1, 2, 5, 9, 8, 7, 9, 3, 3,12, 7, 9, 8, 3, 2,12, 3, 6\r\n",
//            " 9, 2, 1, 8, 4, 8, 1, 8, 6, 2, 3, 9, 1, 7, 3, 8, 5, 8, 5, 4, 4,12, 5, 2, 9, 2, 1, 9, 2, 6, 8, 4, 4,-1,-1,-1,12\r\n",
//            " 7, 7, 2, 8, 4, 4, 1, 9, 8, 2, 9, 8,12, 5, 5, 2, 8, 1, 5, 9, 9,12, 6, 5, 9, 8, 1, 4, 4, 7, 6,12, 4, 9, 1, 8, 2\r\n",
//            " 1, 6, 7, 2, 8, 7, 6,12, 1, 2, 9, 5,12, 7, 6, 4, 9, 2, 2, 5, 1, 9, 2, 1, 6, 8, 3, 2, 8, 1, 2, 6, 9, 8, 3,-1, 2\r\n",
//            " 5, 5, 7,12, 1, 8, 4, 4, 2,12,12, 1, 1, 2, 8, 4, 8, 2, 6, 8, 3, 8, 5, 5, 3, 8,12, 8, 5,12, 1,12, 2, 5, 2,-1, 6\r\n",
//            " 9, 2, 8, 1, 3, 5, 6, 2, 7, 9, 2, 1, 6, 8, 1, 2, 1, 5, 2, 2,12, 2, 4, 9, 2, 2, 4, 7, 4, 3, 6, 9, 6, 5,12, 2, 3\r\n",
//            " 1, 7, 2, 2, 5, 6,12, 6, 6,12,12, 2, 1, 2, 2, 7, 1, 1, 8, 3, 5, 2,12, 1, 8, 2, 6, 3, 2, 9, 3, 2, 4, 9, 8, 5, 3\r\n",
//            " 1, 3, 2, 1, 1, 6, 3,-1, 2, 4, 8, 7, 3, 4, 7, 6, 1, 9, 7, 2,12, 4, 6, 5, 7, 8, 2,12, 1, 2, 6, 7, 8, 2, 3,12, 9\r\n",
//            "3, 6, 4, 9, 2,12, 9, 8, 2, 7, 6, 6, 8, 3, 7, 9, 3, 7, 2, 2, 3, 2, 4, 5, 8, 7, 2,12,12, 4,12, 2,12,-1, 6,-1, 2\r\n",
//            "6, 4, 4,12, 8, 3, 2, 7, 3, 8, 4, 7, 3, 1, 5, 6, 2, 2, 2, 6, 2, 1, 4, 3, 1, 4, 2, 5, 7, 1, 6, 5,12, 7, 5,-1, 3\r\n",
//            "4, 8, 2, 2,12, 9, 3, 3, 8, 7, 7, 8,12, 6,12, 2, 4,12, 2,12, 7, 8, 7, 1, 9, 5,12, 4, 2, 2, 9, 7, 1, 8, 3, 8, 9\r\n",
//            "2, 2, 5, 1, 7, 1, 8, 2,12, 3,12, 5, 7, 9,12,12,12, 2, 4, 4, 2,12, 2, 2, 1, 6, 9,12, 7, 4, 6,12, 8, 4, 8, 2,12\r\n",
//            "3, 1, 2, 8, 1, 4, 7, 9, 3, 7, 3, 6, 6, 6, 3, 9, 9, 3, 9, 3, 3, 7, 5,12, 2, 8, 2, 2, 5, 4, 9, 8, 5, 3, 2, 6, 4\r\n",
//            "12, 1, 9, 5, 9, 2, 6,12, 3, 4,12,-1,12, 7, 9, 2, 1, 2, 2, 4, 6,12, 2, 2, 2, 3, 4, 1, 4, 4, 2, 4,12, 6, 2, 5, 6\r\n"
//    };
//    string startindex="0,0";
//    string goalindex= "36,36";
//    searchable<State<point>> *m=new matrix(temp,startindex,goalindex);
//
//    BFSAlgorithm<vector<State<point>>,State<point>> *algo;
//    algo->Search(m);
//    //algo.


//    return 0;
//}