//
// Created by maayan on 21/01/2020.
//

#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H

#include <vector>
#include "searchable.h"
template <typename Problem,typename Solution>
class Searcher {
public:
    virtual Solution Search(searchable<Problem>* searcable)=0;
};


#endif //MILESTONE2_SEARCHER_H
