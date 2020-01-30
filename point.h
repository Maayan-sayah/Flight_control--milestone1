//
// Created by maayan on 22/01/2020.
//

#ifndef MILESTONE2_POINT_H
#define MILESTONE2_POINT_H


struct point
{
    int first, second;

        bool operator<(const point &rhs) const {
        if (first < rhs.first)
            return true;
        if (rhs.first < first)
            return false;
        return second < rhs.second;
    }

    bool operator==(const point &rhs) const {
        return first == rhs.first &&
               second == rhs.second;
    }

    bool operator!=(const point &rhs) const {
        return !(rhs == *this);
    }
};

#endif //MILESTONE2_POINT_H
