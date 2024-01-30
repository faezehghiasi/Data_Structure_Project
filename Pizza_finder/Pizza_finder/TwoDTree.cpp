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
void TwoDTree:: rangeSearch(double x, double y, double dist) {
    double radius = dist * dist;
    rangeSearch(true, root, x, y, radius);
}
//******************************************************************************
void TwoDTree::rangeSearch(bool divX, BasicNode* node, double x, double y, double radius) {
    double d = node->coordinates.distanceSquared(Point(x, y));
    if (radius >= d) {
        cout << node->name << " " << "location : " << "( " << node->coordinates.x << ", " << node->coordinates.y << " )" << endl;
    }
    double delta = divX ? x - node->coordinates.x : y - node->coordinates.y;
    double delta2 = delta * delta;
    BasicNode* node1 = (delta < 0) ? node->left : node->right;
    BasicNode* node2 = (delta < 0) ? node->right : node->left;
    rangeSearch(!divX, node1, x, y, radius);
    if (delta2 < radius) {
        rangeSearch(!divX, node2, x, y, radius);
    }
}
//***********************************************************************************
