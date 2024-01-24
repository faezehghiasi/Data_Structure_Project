#include "UndoNode.h"
#include<algorithm>
UndoNode::UndoNode(const TwoDTree& nowTree) {
	copy(nowTree.nodes.begin(), nowTree.nodes.end(),this->data.nodes.begin());
	this->data.root = this->data.buildTree(true, this->data.nodes);
	this->next = nullptr;
	this->prev = nullptr;
}