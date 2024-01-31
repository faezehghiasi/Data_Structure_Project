#pragma once
#include"UndoList.h"
#include<vector>
class HashTableOfTrees
{
private:
	vector<UndoList> hashTable;
public:
	HashTableOfTrees(){}
	void insert(UndoList newList);
	//TwoDTree getTreeWithKey(int key);
	friend class UndoList;
	void display(int index);
};

