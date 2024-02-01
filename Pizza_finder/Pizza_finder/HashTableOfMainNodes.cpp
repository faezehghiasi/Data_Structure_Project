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
int HashTableOfMainNodes::search(string key) {
    int i = 0;
    unsigned int index = 0;
    do {
        index = finalHash(key, i);
        if (hashtable[index]->getName() == key) return index;
        i++;
    } while (hashtable[index] != nullptr || hashtable[index]->getIsDeleted() && index < sizeOfTable);
    return -1;
}
//***************************************************************************
void HashTableOfMainNodes::deleteWithKey(string key) {
    int index = search(key);
    if (index != -1) {
        hashtable[index]->setIsDelete(true);
    }
    else throw CustomException("There is no pizzeria with this name in hash table");
}
//*****************************************************************************
void HashTableOfMainNodes::insert(BasicNode* newNode) {
    int i = 0;
    while (i != sizeOfTable) 
    {
        int index = finalHash( newNode->getName(), i);
        if ( hashtable[index] == NULL)
        {
            this->hashtable[index] = newNode;
            //cout << this->hashtable[index]->getName() << endl;
            return;
        }
        if (hashtable[index]->getIsDeleted() == true)
        {
            BasicNode* temp = hashtable[index];
            hashtable[index] = newNode;
            delete temp;
        }
        else i++;
    }
    this->resize();
    this->insert(newNode);
}
//*****************************************************************
void HashTableOfMainNodes::resize() {
    BasicNode** temp = new BasicNode*[sizeOfTable];
    int tempsize = sizeOfTable;
    for (int i = 0; i < sizeOfTable; i++) {
        temp[i] = this->hashtable[i];
    }
    delete[] hashtable;
    sizeOfTable = this->nextPrime(sizeOfTable * 2);
    hashtable =new BasicNode*[sizeOfTable];
    for (int i = 0; i < tempsize; i++)
    {
        this->insert(temp[i]);
    }
    

}
//*****************************************************************
void HashTableOfMainNodes::clear()
{
    delete[] this->hashtable;
    hashtable = new BasicNode*[sizeOfTable];
    for (int i = 0; i < sizeOfTable; i++) {
        hashtable[i] = NULL;
    }
}
