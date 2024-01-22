#pragma once
#include"Node_SubPizza.h"
#include<iostream>
#include<vector>
using namespace std;
class Node_MainPizza:public BasicNode
{
private:
	vector< Node_SubPizza> branches;
public:
	Node_MainPizza(double xVal, double yVal, string nameVal, string mainBranchNameVal)
		: BasicNode(xVal, yVal, nameVal){}
	void addBranch(Node_SubPizza input);
};

