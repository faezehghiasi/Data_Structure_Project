#include "UndoList.h"
void UndoList::pushBack(UndoNode* newNode) {
	if (root == nullptr)root = newNode;
	UndoNode* temp;
	temp = root;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
}
