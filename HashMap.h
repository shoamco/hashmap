//
// Created by shoam on 12/17/19.
//

#ifndef DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
#define DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
#include <string>
#include <list>
#include <vector>
#include <iostream>
typedef size_t(*HashFunc)(const std::string&, size_t);
size_t defaultHashFunc(const std::string&, size_t);
template <typename T>
class HashMap{
public:
    explicit HashMap(size_t hashSize = HASH_TABLE_SIZE, HashFunc func = defaultHashFunc);
    void insert(const std::string, const T&);
    T& operator[](const std::string&);
    const T& operator[](const std::string&) const;
private:
    struct Pair
    {
        Pair(const std::string&, T);
        std::string m_key;
        T m_value;
    };
    static const size_t HASH_TABLE_SIZE = 9;
    typedef std::list<Pair> PairList;
    typedef typename std::list<Pair>::Iterator ListItr;
    typedef std::vector< std::list<Pair> > HashTable;
    size_t m_hashSize;
    HashTable m_table;
    HashFunc m_hashFunc;
    size_t m_bucketsInUse;
    size_t m_numOfPairs;
    Pair& addPair(const Pair&, size_t, HashTable&);
//    ListItr getPairItr(const string&, size_t* slot = NULL);
//    void rehash(size_t newSize = 0);
//    bool isPrime(size_t);
//    size_t validateSize(size_t);
//    size_t getNearestBigEnoughPrimeSize(size_t);
//    template <typename W>
//    friend std::ostream& operator<<(std::ostream& os, const HashMap<W>& map);
    };
//template <typename T>
//inline HashMap<T>::HashMap(size_t hashSize, HashFunc func):m_hashSize(hashSize),m_hashFunc(func){}


template<class T>
inline void HashMap<T>::insert(const std::string key, const T& value){
    bool isPairIn = false;
    size_t index = m_hashFunc(key);
    for (typename std::vector<T>::iterator it = m_table.begin() ; it != m_table.end(); ++it){
        std::cout << "\t" << *it;
    }
}


#endif //DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
