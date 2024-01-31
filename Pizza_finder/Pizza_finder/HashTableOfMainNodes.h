#pragma once
#include"BasicNode.h"

class HashTableOfMainNodes
{
private:
	BasicNode*** hashtable;
	unsigned int sizeOfTable;
	unsigned int hash2(const string& str);
	unsigned int hash1(const string& str);
	unsigned int finalHash(const string& key, int i);
	bool isPrime(int num);
	int nextPrime(int m);
public:
	HashTableOfMainNodes() {
		sizeOfTable = 113;
		hashtable = new BasicNode * *[sizeOfTable];
	}
	int search(string key);
	void deleteWithKey(string key);
	HashTableOfMainNodes():sizeOfTable(113){
		hashtable = new BasicNode**[sizeOfTable];
	}
	void clear();
	void insert(BasicNode**);
	void resize();
};

