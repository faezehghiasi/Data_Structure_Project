#include "TwoDTree.h"
#include<algorithm>
using namespace std;
void TwoDTree::addMainBranch(Node_MainPizza* newPizzaStore) {
    nodes.push_back(newPizzaStore);
    clearTree(root);
    root = buildTree(true, nodes);
}
//****************************************************************************
void TwoDTree::addSubBranch(Node_SubPizza* newPizzaStore) {
    nodes.push_back(newPizzaStore);
    clearTree(root);
    root = buildTree(true, nodes);
}
//****************************************************************************
void TwoDTree::clearTree(BasicNode* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}
//****************************************************************************
BasicNode* TwoDTree::buildTree(bool divX, vector<BasicNode*>nodes) {
    if (nodes.empty()) {
        return nullptr;
    }
    vector<BasicNode*> sortedNodes(nodes);
    if (divX) {
        sort(sortedNodes.begin(), sortedNodes.end(), [](auto a, auto b) {return a->coordinates.x < b->coordinates.x; });
    }
    else {
        sort(sortedNodes.begin(), sortedNodes.end(), [](auto a, auto b) {return a->coordinates.y < b->coordinates.y; });
    }
    int mid = sortedNodes.size() /2;
    BasicNode* newNode;
    if (typeid(*sortedNodes[mid]) == typeid(Node_MainPizza)) {
        newNode = new Node_MainPizza(sortedNodes[mid]->coordinates.x, sortedNodes[mid]->coordinates.y, sortedNodes[mid]->name);
    }
    else {
        Node_SubPizza* temp = dynamic_cast<Node_SubPizza*>(sortedNodes[mid]);
        newNode = new Node_SubPizza(temp->coordinates.x,temp->coordinates.y,temp->name,temp->mainBranchName);
    }
    newNode->left = buildTree(!divX, vector<BasicNode*>(sortedNodes.begin(), sortedNodes.begin() + mid));
    if (mid + 1 <= sortedNodes.size() - 1) {
        newNode->right = buildTree(!divX,vector<BasicNode*>(sortedNodes.begin() + mid + 1, sortedNodes.end()));
    }
    return  newNode;
}
//****************************************************************************
void TwoDTree::deleteNode(Point removeCoor) {
//$$$$$$$$$$$$$$$$$$$$$$$ exception handeling $$$$$$$$$$$$$$$$$$$$$$$$
    auto locOfRmvNode = find_if(this->nodes.begin(), this->nodes.end(), [&](auto a) { return removeCoor == a->coordinates; });
    this->nodes.erase(locOfRmvNode);
    this->clearTree(this->root);
    this->root=this->buildTree(true, this->nodes);
}
//****************************************************************************
BasicNode* TwoDTree::findNearestNeighbourhood(const Point& queryPoint, bool dimention, BasicNode* subroot)
{
    //exist query point in 2dtree
    if (subroot->coordinates == queryPoint)return subroot;
    //subroot be a leaf
    if (subroot->left == NULL and subroot->right == NULL)return subroot;
    BasicNode* nearestNode;
    bool CurrrentBranch_lest = false;
    if (this->isFirstPointSmaller(queryPoint, subroot->coordinates, dimention)) {
        if (subroot->left != NULL) {
            nearestNode = findNearestNeighbourhood(queryPoint, !dimention, subroot->left);
            CurrrentBranch_lest = true;
        }
        else  nearestNode = findNearestNeighbourhood(queryPoint, !dimention, subroot->right);
    }
    else {
        if(subroot->right!=NULL) nearestNode = findNearestNeighbourhood(queryPoint, !dimention, subroot->right);
        else {
            nearestNode = findNearestNeighbourhood(queryPoint, !dimention, subroot->left);
            CurrrentBranch_lest = true;
        }
    }

    if (/*should replace*/)nearestNode = subroot;

    double radius =/*calculate*/;
    double shortDist;//The shortest distance between two points
    if (dimention)shortDist = pow(queryPoint.x - subroot->coordinates.x,2);
    else shortDist = pow(queryPoint.y - subroot->coordinates.y, 2);




}
//***************************************************************************
bool TwoDTree::isFirstPointSmaller(const Point& first, const Point& second, bool dim) {
    if (!dim) {
        if (first.x < second.x)return true;
        else return false;
    }
}

