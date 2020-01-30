//
// Created by maayan on 27/01/2020.
//

#ifndef MILESTONE2_FILECACHMANAGER_H
#define MILESTONE2_FILECACHMANAGER_H

#include <string>
#include <list>
#include <bits/unordered_map.h>
#include <functional>
#include "CacheManager.h"

using namespace std;


class FileCachManager :public CacheManager{
private:
    unsigned int capacityLRU;
    list<string> objectsList;
    unordered_map<string, pair<string, list<string>::iterator>> cacheMap;
public:


    FileCachManager() {
        this->capacityLRU = 10;
    }

    bool inCachManager(string key,string obj){
        auto temp = cacheMap.find(key);
        //if the key in the cache;
        if (!(temp == cacheMap.end())) {
            changeOrder(temp);
            cacheMap[key] = {obj, objectsList.begin()};
            ofstream fp1;
            fp1.open(key + ".txt", ios::binary);
            if (fp1) {
                fp1.write((char *) &obj, sizeof(obj));
                fp1.close();
            }
            return true;
        }
        return false;
    }
     void insert(string key, string obj){

             //if the key isn't in the cache

             ofstream fp;
             fp.open(key + ".txt", ios::binary);
             if (fp) {
                 fp.write((char *) &obj, sizeof(obj));
                 fp.close();
             }

             if (cacheMap.size() >= capacityLRU) {
                 cacheMap.erase(objectsList.back());
                 objectsList.pop_back();
             }
             objectsList.push_front(key);
             cacheMap.insert({key, {obj, objectsList.begin()}});

    }

    string get(string key){
         //check if the cache is null
         if (cacheMap.size() == 0) {
             throw "null cash";
         }
         auto temp = cacheMap.find(key);
         //if the key in the cache
         if (!(temp == cacheMap.end())) {
             //***change the order of object****
             if (cacheMap.size() == 1) {
                 return cacheMap.find(key)->second.first;
             } else {
                 changeOrder(temp);
                 return cacheMap.find(key)->second.first;
             }
         }
             //if the key isn't in the cache
         else if (temp == cacheMap.end()) {

             string obj = readfromfile(obj, key);
             if (cacheMap.size() >= capacityLRU) {
                 cacheMap.erase(objectsList.back());
                 objectsList.pop_back();
             }
             objectsList.push_front(key);
             cacheMap.insert({key, {obj, objectsList.begin()}});
             return obj;

         } else {
             throw "ERROR";
         }
     }

    string readfromfile(string obj, string key){
                 ifstream fp;
        fp.open(key + ".txt", ios::binary);
        if (fp.is_open()) {
            fp.read((char *) &obj, sizeof(obj));
            fp.close();
        }
        else
            throw "ERROR";

        return obj;
     }

     void changeOrder(typename unordered_map<string, pair<string, list<string>::iterator>>::iterator &map){
                 objectsList.erase(map->second.second);
        objectsList.push_front(map->first);
        map->second.second = objectsList.begin();
     }

     void foreach(const function<void(string &)> func){
                 for (string s: this->objectsList) {
            func(this->cacheMap[s].first);
        }
     }
};




#endif //MILESTONE2_FILECACHMANAGER_H
