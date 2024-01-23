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
	Node_MainPizza(double xVal, double yVal, string nameVal): BasicNode(xVal, yVal, nameVal){}
	void addBranch(Node_SubPizza input);
	void print(){}
	friend class TwoDTree;
};

