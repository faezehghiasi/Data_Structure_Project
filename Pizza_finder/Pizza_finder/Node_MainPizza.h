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
	Node_MainPizza(double xVal, double yVal, string nameVal,vector<Node_SubPizza> vVal): BasicNode(xVal, yVal, nameVal){
		for (int i = 0; i < vVal.size(); i++)this->branches.push_back(vVal[i]);
	}
	Node_MainPizza(Point p, string nameVal) : BasicNode(p, nameVal) {}
	void addBranch(Node_SubPizza input);
	void printSubBranches();
	void print();
	friend class TwoDTree;
};

