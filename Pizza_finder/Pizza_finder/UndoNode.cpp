#include "UndoNode.h"
#include<algorithm>
UndoNode::UndoNode(TwoDTree nowTree) {
	data.nodes.clear();
	data.nodes.resize(nowTree.nodes.size());

	for (int i = 0; i < nowTree.nodes.size(); i++) {
		if (typeid(*nowTree.nodes[i]) == typeid(Node_MainPizza)) {
			Node_MainPizza* temp = dynamic_cast<Node_MainPizza*>(nowTree.nodes[i]);
			data.nodes[i] = new Node_MainPizza(temp->getCoordinates().getX(), temp->getCoordinates().getY(), temp->getName(),temp->getBranches());
		}
		else {
			Node_SubPizza* temp = dynamic_cast<Node_SubPizza*>(nowTree.nodes[i]);
			data.nodes[i] = new Node_SubPizza(temp->getCoordinates().getX(), temp->getCoordinates().getY(), temp->getName(),temp->getMainBranchName());
		}
	}
	this->data.root = this->data.buildTree(true, this->data.nodes,true);
	this->next = nullptr;
	this->prev = nullptr;
}