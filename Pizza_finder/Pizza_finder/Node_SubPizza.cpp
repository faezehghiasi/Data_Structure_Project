#include "Node_SubPizza.h"
void Node_SubPizza::print() {
	cout << name << " " << "location : " << "( " << coordinates.x << ", " << coordinates.y << " )" << endl;
}
string Node_SubPizza::getMainBranchName() { return mainBranchName; }