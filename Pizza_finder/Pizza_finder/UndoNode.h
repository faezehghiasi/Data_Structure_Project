#pragma once
#include"TwoDTree.h"
class UndoNode
{
private:
	TwoDTree data;
	TwoDTree* next;
	TwoDTree* prev;
public:
	UndoNode():next(nullptr),prev(nullptr){}
	UndoNode(const TwoDTree& nowTree);
};

