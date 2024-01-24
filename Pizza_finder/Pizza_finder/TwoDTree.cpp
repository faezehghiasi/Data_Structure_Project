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
// ############## incompelte #################3
//void TwoDTree::deleteNode(Point removeCoor) {
//
//
//    if (root == NULL)return;//exception handeling of empty tree
//
//
//    bool dimension = true;
//    if (removeCoor == this->root->coordinates) {
//        BasicNode* removeNode = root;
//       this->nodes.erase( find(this->nodes.begin(), this->nodes.end(), root));
//        
//       root = buildTree(dimension, this->nodes);
//       return;
//    }
//
//    if(dimension){
//    //dimention is x
//        if(removeCoor.x<=this->root->coordinates.x)
//    }
//    else{}
//
//}
//****************************************************************************
