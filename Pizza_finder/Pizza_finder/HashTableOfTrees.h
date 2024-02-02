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
	TwoDTree getTreeWithKeyAndChainNumber(int key,int chainNumber);
	friend class UndoList;
	void display(int index);
	TwoDTree backToPeresent();
};

