#include "HashTableOfMainNodes.h"
#include"CustomException.h"
#include<array>
unsigned int HashTableOfMainNodes::hash1(const string& str) {
    const unsigned int fnv_prime = 0x01000193;
    unsigned int hash_value = 0x811c9dc5;

    for (char byte : str) {
        hash_value ^= byte;
        hash_value *= fnv_prime;
    }

    return hash_value % this->sizeOfTable;
}
//******************************************************************
bool HashTableOfMainNodes:: isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}
//******************************************************************
int HashTableOfMainNodes:: nextPrime(int m) {
    int next = m + 1;
    while (true) {
        if (isPrime(next)) {
            return next;
        }
        next++;
    }
}
//******************************************************************
//unsigned int HashTableOfMainNodes:: hash2(const string& str) {
//    unsigned long hash = 5381;
//    for (char ch : str) {
//        hash = ((hash << 5) + hash) + ch; // hash * 33 + ch
//    }
//    return hash % sizeOfTable;
//}
//******************************************************************
unsigned int HashTableOfMainNodes::finalHash(const string& key, int i) {
    int index = (hash1(key) + i) % sizeOfTable;
    return index;
}
//******************************************************************
int HashTableOfMainNodes::search(string key) {
    int i = 0;
    unsigned int index = 0;
    while (hashTable[index] != nullptr || index < sizeOfTable) {
        index = finalHash(key, i);
        if (hashTable[index] == NULL)return -1;
        if (hashTable[index]->getName() == key) return index;
        i++;
    }
    return -1;
}

//*****************************************************************************
void HashTableOfMainNodes::insert(BasicNode* newNode) {
    int i = 0;
    while (i != sizeOfTable) 
    {
        int index = finalHash(newNode->getName(), i);
        if (hashTable[index] == NULL)
        {
            hashTable[index] = newNode;
            return;
        }
        else i++;
    }
    this->resizeHashTable();
    this->insert(newNode);
}
//*****************************************************************
void HashTableOfMainNodes::resizeHashTable() {
    int tempsize = sizeOfTable;
    vector<BasicNode*>temp(tempsize);
    for (int i = 0; i < tempsize; i++)temp[i] = hashTable[i];
    hashTable.clear();
    sizeOfTable = this->nextPrime(sizeOfTable * 2);
    hashTable.resize(sizeOfTable);
    for (int i = 0; i < tempsize; i++)
    {
        this->insert(temp[i]);
    }
}
//*****************************************************************
void HashTableOfMainNodes::clearHashTable() {
    hashTable.clear();
    hashTable.resize(sizeOfTable);
}
