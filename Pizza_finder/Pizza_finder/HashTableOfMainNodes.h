#pragma once
#include"BasicNode.h"
#include<vector>
class HashTableOfMainNodes
{
private:

	unsigned int sizeOfTable;
	//unsigned int hash2(const string& str);
	unsigned int hash1(const string& str);
	unsigned int finalHash(const string& key, int i);
	bool isPrime(int num);
	int nextPrime(int m);
public:
	vector<BasicNode**>hashTable;
	int search(string key);
	HashTableOfMainNodes():sizeOfTable(11){
		hashTable.resize(11);
		for (int i = 0; i < sizeOfTable; i++) {
			(hashTable[i]) = new BasicNode*;
			*hashTable[i] = nullptr;
		}
	}
	void insert(BasicNode**);
	void resizeHashTable();
	void clearHashTable();

};

