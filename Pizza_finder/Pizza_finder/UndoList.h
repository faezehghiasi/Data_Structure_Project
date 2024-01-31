#pragma once
#include"UndoNode.h"
class UndoList
{
private:
	UndoNode* root;
public:
	UndoList() :root(nullptr){}
	void pushBack(UndoNode*);
	friend class HashTableOfTrees;
};

