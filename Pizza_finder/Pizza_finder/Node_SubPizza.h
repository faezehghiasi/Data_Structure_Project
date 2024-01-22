#pragma once
#include"BasicNode.h"
class Node_SubPizza :public BasicNode
{
	string mainBranchName;
public:
	Node_SubPizza(double xVal, double yVal, string nameVal, string mainBranchNameVal)
		:BasicNode(xVal, yVal, nameVal), mainBranchName(mainBranchNameVal) {}

};

