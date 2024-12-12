#pragma once
#include"BasicNode.h"
class Node_SubPizza :public BasicNode
{
	string mainBranchName;
public:
	Node_SubPizza(double xVal, double yVal, string nameVal, string mainBranchNameVal)
		:BasicNode(xVal, yVal, nameVal), mainBranchName(mainBranchNameVal) {}
	Node_SubPizza(Point p, string nameVal, string mainBranchNameVal)
		:BasicNode(p, nameVal), mainBranchName(mainBranchNameVal) {}
	void print();
	string getMainBranchName();
	friend class TwoDTree;
};

