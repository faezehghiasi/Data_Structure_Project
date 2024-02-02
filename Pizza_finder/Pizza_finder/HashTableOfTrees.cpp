#include "HashTableOfTrees.h"
void HashTableOfTrees::insert(UndoList newList) {
	hashTable.push_back(newList);
}
//*******************************************************
TwoDTree HashTableOfTrees::getTreeWithKeyAndChainNumber(int key, int chainNumber) {
	if (key > hashTable.size())throw("No command has been applied at this time");
	return hashTable[key - 1].getDataWithIndex(chainNumber);
}
//********************************************************
void HashTableOfTrees::display(int index) {
	this->hashTable[index].root->data.display(this->hashTable[index].root->data.root);
}
//*******************************************************
