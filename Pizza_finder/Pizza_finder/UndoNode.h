#pragma once
#include"TwoDTree.h"
class UndoNode
{
private:
	TwoDTree data;
	UndoNode* next;
	UndoNode* prev;
public:
	UndoNode():next(nullptr),prev(nullptr){}
	UndoNode(const TwoDTree& nowTree);
	friend class UndoList;
};

