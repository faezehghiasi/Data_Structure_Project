#pragma once
#include"BasicNode.h"

class HashTableOfMainNodes
{
private:

	unsigned int sizeOfTable;
	unsigned int hash2(const string& str);
	unsigned int hash1(const string& str);
	unsigned int finalHash(const string& key, int i);
	bool isPrime(int num);
	int nextPrime(int m);
public:
	BasicNode** hashtable;
	int search(string key);
	void deleteWithKey(string key);
	HashTableOfMainNodes():sizeOfTable(113){
		hashtable = new BasicNode*[sizeOfTable];
		for (int i = 0; i < sizeOfTable; i++) {
			hashtable[i] = NULL;
		}
			
	}
	void clear();
	void insert(BasicNode*);
	void resize();
};

