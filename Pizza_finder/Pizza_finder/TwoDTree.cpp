#include "TwoDTree.h"
#include<algorithm>
#include"CustomException.h"
#include"HashTableOfMainNodes.h"
using namespace std;
extern HashTableOfMainNodes hashTableOfMainNodes;
void TwoDTree::addMainBranch(Node_MainPizza* newPizzaStore) {
    nodes.push_back(newPizzaStore);
    clearTree(root);
    hashTableOfMainNodes.clear();
    root = buildTree(true, nodes);
}
//****************************************************************************
void TwoDTree::addSubBranch(Node_SubPizza* newPizzaStore) {
    nodes.push_back(newPizzaStore);
    clearTree(root);
    hashTableOfMainNodes.clear();
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
    auto locOfRmvNode = find_if(this->nodes.begin(), this->nodes.end(), [&](auto a) { return removeCoor == a->coordinates; });
    this->nodes.erase(locOfRmvNode);
    this->clearTree(this->root);
    hashTableOfMainNodes.clear();
    this->root=this->buildTree(true, this->nodes);
}
//****************************************************************************
void TwoDTree:: rangeSearch(double x, double y, double dist) {
    double radius = dist * dist;
    static bool res = false;
    rangeSearch(true, root, x, y, radius,res);
    if (!res) throw CustomException("There is no pizzeria in the desired radius around this point!");
}
//******************************************************************************
void TwoDTree::rangeSearch(bool divX, BasicNode* node, double x, double y, double radius,bool& res) {
    if (node == nullptr) {
        return;
    }
    double d = node->coordinates.distanceSquared(Point(x, y));
    if (radius >= d) {
        res = true;
        cout << node->name << " " << "location : " << "( " << node->coordinates.x << ", " << node->coordinates.y << " )" << endl;
    }
    double delta = divX ? x - node->coordinates.x : y - node->coordinates.y;
    double delta2 = delta * delta;
    BasicNode* node1 = (delta <= 0) ? node->left : node->right;
    BasicNode* node2 = (delta <= 0) ? node->right : node->left;
    rangeSearch(!divX, node1, x, y, radius,res);
    if (delta2 < radius) {
        rangeSearch(!divX, node2, x, y, radius,res);
    }
}
//***********************************************************************************
bool TwoDTree:: shoulReplace(Point queryNode, Point currentNode, Point otherNode)
{

    if (queryNode.distanceSquared(currentNode) < queryNode.distanceSquared(otherNode))return false;
    return true;

}
//***************************************************************************
BasicNode* TwoDTree::findNearestNeighbourhood(Point queryPoint, bool dimention, BasicNode* subroot)
{
    //$$$$$$$$$$$$$$$$$$$$$ if two point has same distance it returns one $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

    //exist query point in 2dtree
    if (subroot->coordinates == queryPoint)return subroot;
    //subroot be a leaf
    if (subroot->left == NULL and subroot->right == NULL)return subroot;
    BasicNode* nearestNode;
    bool CurrrentBranch_left = false;
    if (this->isFirstPointSmaller(queryPoint, subroot->coordinates, dimention)) 
    {
        if (subroot->left != NULL) 
        {
            nearestNode = findNearestNeighbourhood(queryPoint, !dimention, subroot->left);
            CurrrentBranch_left = true;
        }
        else  nearestNode = findNearestNeighbourhood(queryPoint, !dimention, subroot->right);
    }
    else 
    {
        if (subroot->right != NULL) nearestNode = findNearestNeighbourhood(queryPoint, !dimention, subroot->right);
        else
        {
            nearestNode = findNearestNeighbourhood(queryPoint, !dimention, subroot->left);
            CurrrentBranch_left = true;
        }
    }
    if (this->shoulReplace(queryPoint, nearestNode->coordinates, subroot->coordinates))nearestNode = subroot;

    double radius = queryPoint.distanceSquared(nearestNode->coordinates);
    double shortDist;//The shortest distance between two points
    if (dimention)shortDist = pow(queryPoint.x - subroot->coordinates.x, 2);
    else shortDist = pow(queryPoint.y - subroot->coordinates.y, 2);
    if (radius >= shortDist) 
    {
        if (CurrrentBranch_left)
        {
            if (subroot->right != NULL) 
            {
                BasicNode* tempNear = findNearestNeighbourhood(queryPoint, !dimention, subroot->right);
                if (shoulReplace(queryPoint, nearestNode->coordinates, tempNear->coordinates)) nearestNode = tempNear;
            }
        }
        else 
        {
            if (subroot->left != NULL) 
            {
                BasicNode* tempNear = findNearestNeighbourhood(queryPoint, !dimention, subroot->left);
                if (shoulReplace(queryPoint, nearestNode->coordinates, tempNear->coordinates)) nearestNode = tempNear;
            }
        }
    }
    return nearestNode;

}
//***************************************************************************
bool TwoDTree::isFirstPointSmaller(const Point& first, const Point& second, bool dim) {
    if (!dim) 
    {
        if (first.x < second.x)return true;
        else return false;
    }
    else
    {
        if (first.y < second.y)return true;
        else return false;
    }
}
//***************************************************************************
BasicNode* TwoDTree::getRoot() {
    return this->root;
}
//*************************************************************************
void TwoDTree::display(BasicNode* node) {
    if (node != nullptr) {
        display(node->left);
        display(node->right);
        cout << "X : " << node->coordinates.x << "  Y : " << node->coordinates.y << endl;
    }
}
//*************************************************************************
BasicNode* TwoDTree::searchWithCoordinates(double x, double y) {
    return searchWithCoordinates(true,root, x, y);
}
//*************************************************************************
BasicNode* TwoDTree::searchWithCoordinates(bool divX, BasicNode* node, double x, double y) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->coordinates.x == x && node->coordinates.y == y) {
        return node;
    }
    if (divX) {
        if (node->coordinates.x > x) {
            return searchWithCoordinates(!divX, node->left, x, y);
        }
        else {
            return searchWithCoordinates(!divX, node->right, x, y);
        }
    }
    else {
        if (node->coordinates.y > y) {
            return searchWithCoordinates(!divX, node->left, x, y);
        }
        else {
            return searchWithCoordinates(!divX, node->right, x, y);
        }
    }
}

