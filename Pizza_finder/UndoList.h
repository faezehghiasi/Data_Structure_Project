#pragma once
#include"UndoNode.h"
#include"CustomException.h"
class UndoList
{
private:
	UndoNode* root;
public:
	UndoList() :root(nullptr){}
	void pushBack(UndoNode*);
	TwoDTree getDataWithIndex(int index);
	UndoNode* lastChain();
	friend class HashTableOfTrees;
};

