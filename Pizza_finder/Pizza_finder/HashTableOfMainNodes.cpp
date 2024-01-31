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

