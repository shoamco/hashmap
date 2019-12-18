//
// Created by shoam on 12/17/19.
//
#include <string>
#include <list>
#ifndef DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
#define DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
<typename T>
class HashMap{
    HashMap(size_t hashSize);
    void insert(const std::string,const T& value);
    T&operator[](const std::string& key);
};
#endif //DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
