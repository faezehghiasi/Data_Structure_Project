#include "HashTableOfTrees.h"
void HashTableOfTrees::insert(UndoList newList) {
	hashTable.push_back(newList);
}
//*******************************************************
//TwoDTree HashTableOfTrees::getTreeWithKey(int key) {
//	hashTable[key]
//}
//********************************************************
void HashTableOfTrees::display(int index) {
	this->hashTable[index].root->data.display(this->hashTable[index].root->data.root);
}
//*******************************************************
