#pragma once
#include"Node_SubPizza.h"
#include"Node_MainPizza.h"
#include"BasicNode.h"
#include<vector>
using namespace std;
class TwoDTree
{
private:
	BasicNode* root;
	vector<BasicNode*>nodes;
	void clearTree(BasicNode*);
	BasicNode* buildTree(bool, vector<BasicNode*>);
	void rangeSearch(bool divX, BasicNode* node, double x, double y, double radius);
public:
	TwoDTree():root(nullptr){}
	void addMainBranch(Node_MainPizza*);
	void addSubBranch(Node_SubPizza*);
	void deleteNode(Point removeCoord);
	friend class UndoNode;
	void rangeSearch(double x, double y, double radius);

};

