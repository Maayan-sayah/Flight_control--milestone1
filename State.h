//
// Created by maayan on 20/01/2020.
//

#ifndef MILESTONE2_STATE_H
#define MILESTONE2_STATE_H

template <typename T>
class State {
private:
    T currentstate; // todo change to T* (cause now it's calling T's constructor - which may or may not exist)
    int cost=0;
    T cameFrom={-1,-1};
    int direction=0;
public:

    State(T s,int c,T came, int d){;
        this->currentstate=s;
        this->cost=c;
        this->cameFrom=came;
        this->direction=d;
    }

    bool operator==(const State &rhs) const {
        return currentstate == rhs.currentstate;
    }

//    bool operator<(const State &rhs) const {
//        return direction>rhs.direction;
//    }

    bool operator<(const State &rhs) const {
        return direction < rhs.direction;
    }

    bool operator>(const State &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const State &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const State &rhs) const {
        return !(*this < rhs);
    }

    bool operator!=(const State &rhs) const {
        return !(rhs == *this);
    }

    State(T s){
        this->currentstate=s;
    }

    void setCost(int newcost) {
        this->cost = newcost;
    }


    void setDirection(int newdirection) {
        this->direction = newdirection;
    }

    int getDirection() const {
        return direction;
    }

    T getCurrentstate() {
    return currentstate;
    }

    double getCost() const {
        return cost;
    }

    T getCameFrom() {
        return cameFrom;
    }
    void setCameFrom(T newcameFrom) {
        State::cameFrom = newcameFrom;
    }
};

#endif //MILESTONE2_STATE_H
