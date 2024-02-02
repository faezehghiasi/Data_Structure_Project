#pragma once
#include"Node_SubPizza.h"
#include"Node_MainPizza.h"
#include"BasicNode.h"
#include"Neighbourhood.h"
#include<vector>
using namespace std;
class TwoDTree
{
private:
	
	vector<BasicNode*>nodes;
	void clearTree(BasicNode*);
	BasicNode* buildTree(bool, vector<BasicNode*>,bool isUndoNode);
	void rangeSearch(bool divX, BasicNode* node, double x, double y, double radius, bool& res);
	BasicNode* searchWithCoordinates(bool divX, BasicNode* node, double x, double y);
	void merge(vector<pair<string, int>>& inputArray, vector<pair<string, int>> tempArray, int low, int mid, int hi);
	void Sort(vector<pair<string, int>>& inputArray, vector<pair<string, int>> tempArray, int low, int hi);
	vector<pair<string, int>> branchesNumbers();
	BasicNode* findNearestNeighbourhood(Point queryPoint, bool dimention, BasicNode* subroot);
public:
	BasicNode* root;



	TwoDTree() :root(nullptr) {}
	void addMainBranch(Node_MainPizza*);
	void addSubBranch(Node_SubPizza*);
	void deleteNode(Point removeCoord);
	bool shoulReplace(Point queryNode,Point currentNode,Point otherNode);
	bool isFirstPointSmaller(const Point& first, const Point& second, bool dim);
	friend class UndoNode;
	void rangeSearch(double x, double y, double radius);
	BasicNode* searchWithCoordinates(double x, double y);
	void updateSubBranchInVectorAndHash(string mainBranchName,BasicNode* subNode);
	void display(BasicNode* node);
	friend class HashTableOfTrees;
	void findNearestSubBranch(Point queryPoint, string mainBranchName);
	void listOfPizzeriasInTheNeighborhood(bool divX, BasicNode* node, vector<BasicNode*>& list, Neighbourhood nb);
	void listOfPizzeriasInTheNeighborhood(vector<BasicNode*>& list, Neighbourhood nb);
	void mostBranches();
	void prinSubBranchesTemp(string mainName);
	void findNearestNeighHelper(Point);
	TwoDTree& operator =(TwoDTree t);
};

