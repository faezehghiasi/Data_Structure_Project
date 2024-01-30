#include "UndoNode.h"
#include<algorithm>
UndoNode::UndoNode(TwoDTree nowTree) {
	for (int i = 0; i < nowTree.nodes.size(); i++) {
		data.nodes.push_back(nowTree.nodes[i]);
	}
	this->data.root = this->data.buildTree(true, this->data.nodes);
	this->next = nullptr;
	this->prev = nullptr;
}