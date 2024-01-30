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
public:
	TwoDTree():root(nullptr){}
	void addMainBranch(Node_MainPizza*);
	void addSubBranch(Node_SubPizza*);
	void deleteNode(Point removeCoord);
	BasicNode* findNearestNeighbourhood(const Point& queryPoint,bool dimention,BasicNode* subroot);
	bool isFirstPointSmaller(const Point& first, const Point& second, bool dim);
	friend class UndoNode;
};

