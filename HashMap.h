//
// Created by shoam on 12/17/19.
//
#include "LinkedList.h"
#ifndef DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
#define DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
#include <string>
//#include <list>
#include <vector>
#include <iostream>
typedef size_t(*HashFunc)(const std::string&, size_t);
 size_t defaultHashFunc(const std::string& key, size_t hashSize);
inline size_t defaultHashFunc(const std::string& key, size_t hashSize)
{
    /**
     default Hash function=
     (size keys )* (sum all keys) *( (Multiplication of all even keys)+(Multiplication of all odd keys))%hashSize
     * */
    size_t size = key.size(), sumAll = 0, evenMult = 1, oddMult = 1;
    for(size_t i = 0; i < size; ++i)
    {
        sumAll += key[i];
        if(i % 2 == 0)//if even
            evenMult *= key[i];
        else
            oddMult *= key[i];
    }
    return (size * sumAll * (evenMult + oddMult)) % hashSize;
}
template <typename T>
class HashMap{
public:
//    explicit HashMap(size_t hashSize = HASH_TABLE_SIZE, HashFunc func = defaultHashFunc);
     HashMap(size_t hashSize = HASH_TABLE_SIZE, HashFunc func = defaultHashFunc);
    void insert(const std::string, const T&);
    T& operator[](const std::string&);
    const T& operator[](const std::string&) const;
//private:
    struct Pair
    {
        Pair(const std::string&, T);
        std::string m_key;
        T m_value;
    };

public:
//    typedef Pair Pair;
    static const size_t HASH_TABLE_SIZE = 11;
    typedef LinkedList<Pair> PairList;
    typedef typename LinkedList<Pair>::Iterator ListItr;
    typedef std::vector<LinkedList<Pair> > HashTable;
//    typedef std::list<Pair> PairList;
//
//    typedef typename std::list<Pair>::Iterator ListItr;
//    typedef std::vector<std::list<Pair> > HashTable;


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
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const HashMap<U>& map);
    };
template <typename T>
inline HashMap<T>::HashMap(size_t hashSize, HashFunc func):m_hashSize(hashSize),m_table(),m_hashFunc(func),m_bucketsInUse(0),m_numOfPairs(0){

    std::cout<<"\nin ctor\n";
}


template<class T>
inline void HashMap<T>::insert(const std::string key, const T& value){
    bool isPairIn = false;
    size_t index = m_hashFunc(key,m_hashSize);
    for (typename std::vector<T>::iterator it = m_table.begin() ; it != m_table.end(); ++it){
        std::cout << "\t" << *it;
    }
}

template <typename U>
inline std::ostream& operator<<(std::ostream& os, const HashMap<U>& map)
{


//    ostream<<"hashMap: \n";
    os << "HashMap size: " << map.m_hashSize << std::endl;
    os << "Num of Pairs: " << map.m_numOfPairs << std::endl;
    for(size_t i = 0; i < map.m_hashSize; ++i)
    {
        os << "Bucket #" << i << ": ";
//        typename LinkedList<typename HashMap<U>::Pair>::Iterator listIter = map.m_table[i].begin();
//        for(; listIter != map.m_table[i].begin(); ++ listIter)
//        {
//            os << "[" << listIter->m_value.m_key << ", " << listIter->m_value.m_value << "] ->";
//        }
        os << std::endl;
    }
    return os;
}
template <typename U>


#endif //DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
