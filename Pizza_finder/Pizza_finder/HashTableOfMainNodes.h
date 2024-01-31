#pragma once
#include"BasicNode.h"
class HashTableOfMainNodes
{
private:
	BasicNode** hashtable[113];
	unsigned int sizeOfTable;
	unsigned int hash2(const string& str);
	unsigned int hash1(const string& str);
	unsigned int finalHash(const string& key, int i);
public:
	HashTableOfMainNodes():sizeOfTable(113){}

};

