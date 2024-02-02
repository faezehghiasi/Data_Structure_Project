#include "Node_MainPizza.h"
void Node_MainPizza::addBranch(Node_SubPizza input) {
	this->branches.push_back(input);
}
//*************************************************************************
void Node_MainPizza::printSubBranches() {
	for (int i = 0; i < branches.size(); i++) {

		cout << branches[i].getName() << " " << "location : " << "( " << branches[i].getCoordinates().getX() << ", " << branches[i].getCoordinates().getY()<< " )" << endl;
	}
}
//*************************************************************************
void Node_MainPizza::print() {
	cout << name << " " << "location : " << "( " << coordinates.x << ", " << coordinates.y << " )" << endl;
}
//*************************************************************************
vector< Node_SubPizza> Node_MainPizza::getBranches() { return branches; }