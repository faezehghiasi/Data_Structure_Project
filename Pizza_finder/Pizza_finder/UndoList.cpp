#include "UndoList.h"
void UndoList::pushBack(UndoNode* newNode) {
	if (root == nullptr) { 
		root = newNode; 
		return;
	}
	UndoNode* temp;
	temp = root;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
}
//***************************************************************
TwoDTree UndoList::getDataWithIndex(int index) {
	UndoNode* temp;
	temp = root;
	int counter = 1;
	while (temp->next != nullptr) {
		if (counter == index)break;
		temp = temp->next;
		counter++;
	}
	if (index != counter) throw CustomException("There is no such this command!");
	else return temp->data;
}
//****************************************************
UndoNode* UndoList::lastChain() {
	UndoNode* temp = root;
	while (temp->next != NULL) temp = temp->next;
	return temp;
}
