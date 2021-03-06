//
// Created by shoam on 12/17/19.
//
//#include "LinkedList.h"
#ifndef DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
#define DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H

#include <string>
#include <list>
#include <vector>
#include <iostream>

struct HashException : public std::invalid_argument {
    explicit HashException(const std::string &reason);
};

typedef size_t(*HashFunc)(const std::string &, size_t);

size_t defaultHashFunc(const std::string &key, size_t hashSize);

template<typename T>
class HashMap {
private:
    struct Pair {
        Pair(const std::string &m_key, T m_value) : m_key(m_key), m_value(m_value) {}

        std::string m_key;
        T m_value;

        bool operator==(const Pair &pair) {
            return m_key == pair.m_key && m_value == pair.m_value;
        }

        bool operator!=(const Pair &pair) {
            return !operator==(pair);
        }


    };

public:
    explicit HashMap(size_t hashSize = HASH_TABLE_SIZE, HashFunc func = defaultHashFunc);

    void insert(const std::string, const T &);

    T &operator[](const std::string &);//set
    const T &operator[](const std::string &) const;//get value

    static const size_t HASH_TABLE_SIZE = 72;
    typedef std::list<Pair> PairsList;
    typedef typename std::list<Pair>::iterator ListItr;
    typedef typename std::list<Pair>::const_iterator ConstListItr;
    typedef std::vector<std::list<Pair> > HashTable;


    Pair &addPair(const Pair &, size_t, HashTable &);

    ListItr getPairItr(const std::string &, size_t *slot = NULL);

    void rehash(size_t newSize = 0);

    bool isPrime(size_t);

    size_t validateSize(size_t);

    size_t getNearestBigEnoughPrimeSize(size_t);

    void remove(const std::string &);

    void setHashFunc(HashFunc);

    void setHashSize(size_t);

    float getUtilization() const;

    size_t getNumOfBucketsInUse() const;

    size_t getNumOfPairs() const;

    size_t getHashSize() const;

    size_t getIndexByKey(const std::string key);

    T getValueByKey(const std::string key);

    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const HashMap<U> &map);



    T &getPairValueRef(const size_t idx, const std::string &key);

    HashTable m_table;
private:
    size_t m_hashSize;

    HashFunc m_hashFunc;
    size_t m_bucketsInUse;
    size_t m_numOfPairs;

    HashMap &operator=(const HashFunc &);//private assignment operator
};

//template<typename T>
//inline HashMap<T> HashMap<T>::&operator=(const HashFunc &){
//
//}
template<typename T>
inline HashMap<T>::HashMap(size_t hashSize, HashFunc func) {
//    std::cout << "HashMap c-tor" << std::endl;
    m_hashSize = hashSize;
    m_bucketsInUse = 0;
    m_hashFunc = func;
    m_table = HashTable(hashSize);
    m_numOfPairs = 0;


}

template<class T>
inline size_t HashMap<T>::getIndexByKey(const std::string key) {
    return defaultHashFunc(key, m_hashSize);
}

template<typename T>
inline void HashMap<T>::insert(const std::string key, const T &value) {
    /**
     insert key to the hash map,the index is calculate  by the hash function
     if key not in the hash table-push to the linked list of this index
     else  set the value of the index
     * */
    bool isPairInTable = false;
    size_t index = getIndexByKey(key);
    ListItr it = m_table[index].begin();
    for (it; it != m_table[index].end(); ++it) {
        if (it->m_key == key) {//if key in table-set value
            it->m_value = value;
            isPairInTable = true;
            break;
        }
    }
    if (!isPairInTable) {//add new key to table
        Pair pair(key, value);
        m_table[index].push_back(pair);
        m_numOfPairs++;
    }

}

template<typename U>
inline std::ostream &operator<<(std::ostream &os, const HashMap<U> &map) {


    os << "\n*****hashMap:**** \n";
    os << "HashMap size: " << map.m_hashSize << std::endl;
    os << "Num of Pairs: " << map.m_numOfPairs << std::endl;

    for (size_t i = 0; i < map.m_hashSize; ++i) {
        typename HashMap<U>::ConstListItr it ;//const iterator(pair must const iterator)
        std::cout << "Bucket #" << i << ": ";
        for (it = map.m_table[i].begin(); it !=map.m_table[i].end(); ++it) {
//            Pair pair( it->m_key,it->m_value);
//            newHashMap.insert(it->m_key,it->m_value);
            std::cout << "[" << it->m_key << ", " << it->m_value << "] ->";


        }
        std::cout << std::endl;
//        os << "Bucket #" << i << ": ";
//        map.printIndexedList(i);

    }
    return os;
}

template<typename T>
inline T &HashMap<T>::getPairValueRef(const size_t idx, const std::string &key) {
    ListItr it = m_table[idx].begin();
    for (; it != m_table[idx].end(); ++it) {
        if ((*it).m_key == key) {
            return it->m_value.m_value;
        }
    }
}


inline size_t defaultHashFunc(const std::string &key, size_t hashSize) {
    /**
     default Hash function=
     (size keys )* (sum all keys) *( (Multiplication of all even keys)+(Multiplication of all odd keys))%hashSize
     * */
    size_t size = key.size(), sumAll = 0, evenMult = 1, oddMult = 1;
    for (size_t i = 0; i < size; ++i) {
        sumAll += key[i];
        if (i % 2 == 0)//if even
            evenMult *= key[i];
        else
            oddMult *= key[i];
    }
    return (size * sumAll * (evenMult + oddMult)) % hashSize;
}

template<typename T>
inline size_t HashMap<T>::getNumOfBucketsInUse() const {
    size_t num_buckets = 0;
    for (size_t i = 0; i < m_hashSize; ++i) {
        if (m_table[i].size()) {
            ++num_buckets;
        }

    }
    return num_buckets;
}

template<typename T>
inline size_t HashMap<T>::getHashSize() const {
    return m_hashSize;
}

template<typename T>
inline float HashMap<T>::getUtilization() const {
    return float(getNumOfBucketsInUse()) / getHashSize();
}

template<typename T>
inline void HashMap<T>::remove(const std::string &key) {
    /**
     remove item from the hash map-get a key and remove it from the hash table
     * */
    size_t index = getIndexByKey(key);
    ListItr it = m_table[index].begin();
    Pair pair(key, getValueByKey(key));
    m_table[index].remove(pair);
    --m_numOfPairs;

}

template<typename T>
inline T HashMap<T>::getValueByKey(const std::string key) {

    size_t idx = getIndexByKey(key);
    ListItr it = m_table[idx].begin();
    for (; it != m_table[idx].end(); ++it) {
        if ((*it).m_key == key) {
            return it->m_value;
        }
    }
    return NULL;
//    exit(0);

}

template<typename T>
inline T &HashMap<T>::operator[](const std::string &key) {
    size_t idx = getIndexByKey(key);
    ListItr it = m_table[idx].begin();
    for (; it != m_table[idx].end(); ++it) {
        if ((*it).m_key == key) {
            return it->m_value;
        }
    }
    exit(0);
}

template<typename T>
inline void HashMap<T>::rehash(size_t newSize) {
    /**
      rehash-get a new size to hash table
      and rearrange all keys in the new hash table with the new size
     **/
    HashMap<T> newHashMap(newSize);
    for (size_t i = 0; i < m_hashSize; ++i) {
        ConstListItr it ;


        for (it = m_table[i].begin(); it != m_table[i].end(); ++it) {
            Pair pair( it->m_key,it->m_value);
            newHashMap.insert(it->m_key,it->m_value);
        }

    }
    m_table = newHashMap.m_table;
    m_hashSize=newSize;

}

template<typename T>
inline void HashMap<T>::setHashFunc(HashFunc hashFunc) {
    m_hashFunc = hashFunc;
    rehash(m_hashSize );//Rearrange all keys
}

template<typename T>
inline void HashMap<T>::setHashSize(size_t newHashSize) {

    rehash(newHashSize );//Rearrange all keys

}

template<typename T>

inline size_t HashMap<T>::getNumOfPairs() const {
    return m_numOfPairs;
}

#endif //DATA_STRUCTURES_HASHMAP_TEMPLATED_SHOAMCO_HASHMAP_H
