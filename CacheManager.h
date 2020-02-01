//
// Created by maayan on 18/01/2020.
//

#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
using namespace std;

class CacheManager {
private:

public:
    virtual void insert(string key, string obj)=0;

    virtual string get(string key)=0;

    virtual string readfromfile(string obj, string key)=0;

    virtual void changeOrder(typename unordered_map<string, pair<string, list<string>::iterator>>::iterator &map)=0;

    virtual void foreach(const function<void(string &)> func)=0;
    virtual bool inCachManager(string key,string obj)=0;

    virtual ~CacheManager() {

    }

};


#endif //MILESTONE2_CACHEMANAGER_H
