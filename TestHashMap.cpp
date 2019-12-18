//
// Created by shoam on 12/17/19.
//

#include "TestHashMap.h"

void test_create_hash_map() {
    std::cout << "\n***test_create_hash_map ****\n\n";
    HashMap<int> hashMap(3);
//    HashMap<int> hashMap(5);
    std::cout << hashMap;
}

void test_insert() {
    std::cout << "\n***test_insert ****\n\n";
    HashMap<int> hashMap(3);
    hashMap.insert("shoam", 1);
    std::cout << hashMap;
    hashMap.insert("cohen", 2);
    std::cout << hashMap;
    hashMap.insert("a", 44);
    std::cout << hashMap;
    hashMap.insert("shoam", 999);
    std::cout << hashMap;
}


void test_operator_set() {
    std::cout << "\n***test operator [] ****\n\n";
    HashMap<int> hashMap(3);
//    std::cout<<;
//    hashMap[0];
}
void test_getNumOfBucketsInUse(){
    std::cout << "\n*** test_getNumOfBucketsInUse ****\n\n";
    HashMap<int> hashMap(3);
    hashMap.insert("shoam", 1);
    hashMap.insert("cohen", 2);
    hashMap.insert("a", 44);
    std::cout << hashMap;
    std::cout<<"Num Of Buckets In Use: "<<hashMap.getNumOfBucketsInUse()<<std::endl;
    HashMap<int> hashMap2(3);
    std::cout<<"empty-Num Of Buckets In Use: "<<hashMap2.getNumOfBucketsInUse()<<std::endl;


}
void test_getter()
{
    std::cout << "\n*** test_getHashSize ****\n\n";
    HashMap<int> hashMap(3);
    hashMap.insert("shoam", 1);
    hashMap.insert("cohen", 2);
    std::cout << hashMap;
    std::cout<<"getHashSize "<<hashMap.getHashSize()<<std::endl;
    std::cout<<"getNumOfBucketsInUse "<<hashMap.getNumOfBucketsInUse()<<std::endl;
    std::cout<<"getUtilization()  "<<hashMap.getUtilization()<<std::endl;

}
