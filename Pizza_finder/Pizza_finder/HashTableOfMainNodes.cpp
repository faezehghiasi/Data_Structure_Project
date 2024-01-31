#include "HashTableOfMainNodes.h"

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
unsigned int HashTableOfMainNodes:: hash2(const string& str) {
    unsigned long hash = 5381;
    for (char ch : str) {
        hash = ((hash << 5) + hash) + ch; // hash * 33 + ch
    }
    return hash % sizeOfTable;
}
//******************************************************************
unsigned int HashTableOfMainNodes::finalHash(const string& key, int i) {
    int index = (hash1(key) + i * hash2(key)) % sizeOfTable;
    return index;
}
//******************************************************************
void HashTableOfMainNodes::insert(BasicNode** newNode) {
    int i = 0;
    while (i != sizeOfTable) {
        int index = finalHash((* newNode)->getName(), i);
        if (this->hashtable[index] == NULL) {
            this->hashtable[index] = newNode;
            return;
        }
        else i++;
    }
    this->resize();
    this->insert(newNode);
}
//*****************************************************************
void HashTableOfMainNodes::resize() {
    BasicNode*** temp = new BasicNode * *[sizeOfTable * 2];
    for (int i = 0; i < sizeOfTable; i++) {
        temp[i] = this->hashtable[i];
    }
    delete[] hashtable;
    hashtable = temp;
    sizeOfTable = this->nextPrime(sizeOfTable * 2);

}