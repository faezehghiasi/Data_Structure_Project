#include "TwoDTree.h"
#include<algorithm>
#include"CustomException.h"
#include"HashTableOfMainNodes.h"
using namespace std;
extern HashTableOfMainNodes hashTableOfMainNodes;
void TwoDTree::addMainBranch(Node_MainPizza* newPizzaStore) {
    nodes.push_back(newPizzaStore);
    clearTree(root);
    hashTableOfMainNodes.clearHashTable();
    root = buildTree(true, nodes,false);
}
//****************************************************************************
void TwoDTree::addSubBranch(Node_SubPizza* newPizzaStore) {
    nodes.push_back(newPizzaStore);
    clearTree(root);
    hashTableOfMainNodes.clearHashTable();
    root = buildTree(true, nodes,false);
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
BasicNode* TwoDTree::buildTree(bool divX, vector<BasicNode*>nodes,bool isUndoNode) {
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
        Node_MainPizza* temp = dynamic_cast<Node_MainPizza*>(sortedNodes[mid]);
        newNode = new Node_MainPizza(temp->coordinates.x, temp->coordinates.y, temp->name,temp->branches);

        if (!isUndoNode) {
            hashTableOfMainNodes.insert(newNode);
        }
    }
    else {
        Node_SubPizza* temp = dynamic_cast<Node_SubPizza*>(sortedNodes[mid]);
        newNode = new Node_SubPizza(temp->coordinates.x,temp->coordinates.y,temp->name,temp->mainBranchName);
    }
    newNode->left = buildTree(!divX, vector<BasicNode*>(sortedNodes.begin(), sortedNodes.begin() + mid),isUndoNode);
    if (mid + 1 <= sortedNodes.size() - 1) {
        newNode->right = buildTree(!divX,vector<BasicNode*>(sortedNodes.begin() + mid + 1, sortedNodes.end()),isUndoNode);
    }
    return  newNode;
}
//****************************************************************************
void TwoDTree::deleteNode(Point removeCoor) {
    auto locOfRmvNode = find_if(this->nodes.begin(), this->nodes.end(), [&](auto a) { return removeCoor == a->coordinates; });
    auto locOfMainRmvNode = find_if(this->nodes.begin(), this->nodes.end(), [=](auto a) { return a->name == dynamic_cast<Node_SubPizza*>(*locOfRmvNode)->getMainBranchName(); });
    auto locOfRmvNodeInBranchesOfMain = find_if(dynamic_cast<Node_MainPizza*>(*locOfMainRmvNode)->branches.begin(), dynamic_cast<Node_MainPizza*>(*locOfMainRmvNode)->branches.end(), [&](auto a) {return a.coordinates == removeCoor; });
    dynamic_cast<Node_MainPizza*>(*locOfMainRmvNode)->branches.erase(locOfRmvNodeInBranchesOfMain);
    this->nodes.erase(locOfRmvNode);
    this->clearTree(this->root);
    hashTableOfMainNodes.clearHashTable();
    this->root=this->buildTree(true, this->nodes,false);
}
//****************************************************************************
void TwoDTree:: rangeSearch(double x, double y, double dist) {
    double radius = dist * dist;
    bool res = false;
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
    if (subroot == NULL)throw CustomException("The tree is empty!");
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
//*************************************************************************
void TwoDTree::updateSubBranchInVectorAndHash(string mainBranchName,BasicNode* subNode) {
   
    auto it = find_if(nodes.begin(), nodes.end(), [&](auto p) {
        return p->name == mainBranchName; });
    if (it != nodes.end()) {
        dynamic_cast<Node_MainPizza*>(*it)->branches.push_back(*(dynamic_cast<Node_SubPizza*>(subNode)));
    }
    int index = hashTableOfMainNodes.search(mainBranchName);
    dynamic_cast<Node_MainPizza*>(hashTableOfMainNodes.hashTable[index])->branches.push_back(*(dynamic_cast<Node_SubPizza*>(subNode)));
}
//**************************************************************************
void TwoDTree::findNearestSubBranch(Point queryPoint, string mainBranchName) {
   int index= hashTableOfMainNodes.search(mainBranchName);
   if (index == -1)throw CustomException("There is no main branch pizzeria with this name!");
   TwoDTree tempTree;
   int countOfSubBranchs = dynamic_cast<Node_MainPizza*>(hashTableOfMainNodes.hashTable[index])->branches.size();
   if (countOfSubBranchs == 0)throw CustomException("This main branch doesn't have any sub branches!");
   for (int i = 0; i < countOfSubBranchs; i++)tempTree.nodes.push_back(&dynamic_cast<Node_MainPizza*>(hashTableOfMainNodes.hashTable[index])->branches[i]);
   tempTree.root = buildTree(true, tempTree.nodes, false);
   auto near= findNearestNeighbourhood(queryPoint, true, tempTree.root);
   near->print();

}
//***************************************************************************
void TwoDTree::listOfPizzeriasInTheNeighborhood(vector<BasicNode*>& list, Neighbourhood nb) {
    listOfPizzeriasInTheNeighborhood(true, root, list, nb);
}
//***************************************************************************
void TwoDTree::listOfPizzeriasInTheNeighborhood(bool divX, BasicNode* node, vector<BasicNode*>& list, Neighbourhood nb) {
   
    if (node == nullptr)return;
    if (nb.isPointInsideNeighbourhood(node->coordinates)) list.push_back(node);
    if (divX) {
        if (node->coordinates.x >= nb.getTopLeft().x && node->coordinates.x <= nb.getBottomRight().x) {
            listOfPizzeriasInTheNeighborhood(!divX, node->left, list, nb);
            listOfPizzeriasInTheNeighborhood(!divX, node->right, list, nb);
        }
        else if (node->coordinates.x > nb.getBottomRight().x) {
            listOfPizzeriasInTheNeighborhood(!divX, node->left, list, nb);
        }
        else {
            listOfPizzeriasInTheNeighborhood(!divX, node->right, list, nb);
        }
    }
    else {
        if (node->coordinates.y >= nb.getBottomRight().y && node->coordinates.y <= nb.getTopLeft().y) {
            listOfPizzeriasInTheNeighborhood(!divX, node->left, list, nb);
            listOfPizzeriasInTheNeighborhood(!divX, node->right, list, nb);
        }
        else if (node->coordinates.y > nb.getTopLeft().y) {
            listOfPizzeriasInTheNeighborhood(!divX, node->left, list, nb);
        }
        else {
            listOfPizzeriasInTheNeighborhood(!divX, node->right, list, nb);
        }
    }

}
//**************************************************************************
void TwoDTree::mostBranches() {
    vector<pair<string, int>> numbersOfBranches = this->branchesNumbers();
    vector<pair<string, int>> result(numbersOfBranches.size());
    if (numbersOfBranches.size() == 0)throw CustomException("Tree is empty!");
    this->Sort(numbersOfBranches, result, 0, numbersOfBranches.size() - 1);
    int index = numbersOfBranches.size()-1;
    cout << "The most branched pizzeria\n";
    while (numbersOfBranches[index].second == numbersOfBranches[numbersOfBranches.size() - 1].second)
    {
        cout << "Name: " << numbersOfBranches[index].first << "  " << "Number of branches : " << numbersOfBranches[index].second << endl;
        if (index == 0)break;
        index--;
       
        
    }

}
//**************************************************************************
vector<pair<string,int>> TwoDTree::branchesNumbers() {
    vector<pair<string,int>> numbersOfBranches;
    for (int i = 0; i < hashTableOfMainNodes.sizeOfTable; i++)
    {
        if (hashTableOfMainNodes.hashTable[i] != NULL)numbersOfBranches.push_back(make_pair(hashTableOfMainNodes.hashTable[i]->name, dynamic_cast<Node_MainPizza*>(hashTableOfMainNodes.hashTable[i])->branches.size()));
    }
    return numbersOfBranches;
}
//*************************************************************
void TwoDTree::merge(vector<pair<string, int>>& inputArray, vector<pair<string, int>> tempArray, int lo, int mid, int hi) {

    for (int k = lo; k <= hi; k++) {
        tempArray[k] = inputArray[k];
    }

    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
        if (i > mid)
            inputArray[k] = tempArray[j++];
        else if (j > hi)
            inputArray[k] = tempArray[i++];
        else if (tempArray[j].second < tempArray[i].second)
            inputArray[k] = tempArray[j++];
        else
            inputArray[k] = tempArray[i++];
    }

}
//*************************************************************
void TwoDTree::Sort(vector<pair<string, int>>& inputArray, vector<pair<string, int>> tempArray, int lo, int hi) {
    if (hi <= lo)
        return;
    int mid = lo + (hi - lo) / 2;
    Sort(inputArray, tempArray, lo, mid);
    Sort(inputArray, tempArray, mid + 1, hi);
    merge(inputArray, tempArray, lo, mid, hi);
}
//*************************************************************
void TwoDTree::prinSubBranchesTemp(string mainName) {
    int index = hashTableOfMainNodes.search(mainName);
    if (index == -1)throw CustomException("There is no main branch pizzeria with this name!");
    if (dynamic_cast<Node_MainPizza*>(hashTableOfMainNodes.hashTable[index])->branches.size() == 0)throw CustomException("This main branch doesn't have any sub branches !");
    dynamic_cast<Node_MainPizza*>(hashTableOfMainNodes.hashTable[index])->printSubBranches();
}
//*************************************************************
void TwoDTree::findNearestNeighHelper(Point queryPoint) {
     auto near=this->findNearestNeighbourhood(queryPoint, true, this->root);
     near->print();
}
//**************************************************************
void TwoDTree::bulidTreeFromTree(TwoDTree newTree) {
    clearTree(root);
    nodes.clear();
    hashTableOfMainNodes.clearHashTable();
    for (int i = 0; i < newTree.nodes.size(); i++) {
        nodes.push_back(newTree.nodes[i]);
    }
    root = buildTree(true, nodes, false);
}
//**************************************************************
TwoDTree& TwoDTree:: operator =(TwoDTree t) {
    this->clearTree(this->root);
    this->nodes.clear();
    for (int i = 0; i < t.nodes.size(); i++)this->nodes.push_back(t.nodes[i]);
    hashTableOfMainNodes.clearHashTable();
    this->root=this->buildTree(true, this->nodes, false);
    return *this;

}
