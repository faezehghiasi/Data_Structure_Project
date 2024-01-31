#include "HashTableOfMainNodes.h"
#include"CustomException.h"
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
int HashTableOfMainNodes::search(string key) {
    int i = 0;
    unsigned int index = 0;
    do {
        index = finalHash(key, i);
        if ((*hashtable[index])->name == key) return index;
        i++;
    } while ((*hashtable[index] != nullptr || (*hashtable[index])->isDeleted) && index < sizeOfTable);
    return -1;
}
//***************************************************************************
void HashTableOfMainNodes::deleteWithKey(string key) {
    int index = search(key);
    if (index != -1) {
        *hashtable[index] = nullptr;
    }
    else throw CustomException("There is no pizzeria with this name in hash table");
}
//*****************************************************************************