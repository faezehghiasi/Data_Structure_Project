#include<iostream>
#include<string>
#include"BasicNode.h"
#include"Neighbourhood.h"
#include"Node_MainPizza.h"
#include"Node_SubPizza.h"
#include"Point.h"
#include"TwoDTree.h"
#include"UndoNode.h"
#include"UndoList.h"
#include"HashTableOfTrees.h"
#include<stdlib.h>
#include<regex>
#include<string.h>
#include<conio.h>
#include <windows.h>
#include"CustomException.h"
#include"HashTableOfMainNodes.h"
#include<fstream>
#include<iostream>
enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Yellow = 6,
	White = 7,
	Gray = 8
};
#pragma warning (disable:4996)
using namespace std;
HashTableOfMainNodes hashTableOfMainNodes;
HashTableOfTrees hashTableOfTrees;
void validCheck(string order, vector<Neighbourhood>& neibhd, TwoDTree& currTree);
void AddBranchPizzeria(string name, string mainBranchName, Point p, TwoDTree& currTree);
void AddMainBranchPizzeria(string name, Point p, TwoDTree& currTree);
void deleteBranchPizzeria(Point p, TwoDTree& currTree);
void help(ConsoleColor textColor, int delayMillis);
void displayListOfPizzeriaInTheNeighbourhood(vector<BasicNode*>& list, TwoDTree& currTree, Neighbourhood& nb);
void undo(int time, int command, TwoDTree& currTree);
void backToThePresent(TwoDTree&);
//*****************************************************************************
bool isNow = true;
int main(void) {
	int i = 0;
	string order;
	string currentOrder;
	vector<Neighbourhood> neighbourhoods;
	TwoDTree currentTree;
	while (true) {
		UndoList listOftrees;
		///system("cls");
		cout << "Enter the command you want : (Enter Exit for end and Help to see order's form) : ";
		getline(cin, order);
		if (order == "Exit")exit(1);
		if (order == "Help"||order =="help") {
			help(ConsoleColor::Yellow, 40);
			continue;
		}
		int it=0;
		do {
			it= order.find("&");
			currentOrder = order.substr(0, it - 1);
			try
			{
				validCheck(currentOrder, neighbourhoods, currentTree);
			}
			catch (int x)
			{
				cout << "Invalid input!" << endl;
				cout << "Enter Help to show the commands..." << endl;
				cout << "Press enter to continue...";
				cin.get();
				break;
			}
			catch (const exception& e) {
				cerr << e.what() << endl;
				cout << "Press enter to continue...";
				cin.get();
				break;
			}
			if (isNow) {
				UndoNode* newTree = new UndoNode(currentTree);
				listOftrees.pushBack(newTree);
				
			}
			if(it!=-1)order = order.substr(it + 3);
		} while (it != -1);

		if (isNow) {
			hashTableOfTrees.insert(listOftrees);
			i++;
		}
		for (int t = 0; t < i; t++) {
			hashTableOfTrees.display(t);
			cout << "-----------------------------------------------------\n";
		}




		

		cin.get();
	}

}
//*******************validation*******************************************************
void validCheck(string order, vector<Neighbourhood>& neibhd, TwoDTree& currTree) {
	if (order.find("Add-N") != -1) {

		regex check("Add-N \\[[a-zA-Z]+\\] \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");
		if (!regex_match(order, check))throw 0;
		string nameOfNei = order.substr(order.find("[") + 1, order.find("]") - 7);
		Point points[5];
		int locOfParentheses = order.find("(");
		string tempOrder, temp2Order;
		tempOrder = order.substr(locOfParentheses);
		int index = 0;
		do {
			temp2Order = tempOrder.substr(0, tempOrder.find(")") + 1);
			string x, y;
			x = temp2Order.substr(1, temp2Order.find(",") - 1);
			y = temp2Order.substr(temp2Order.find(",") + 1, temp2Order.find(")") - 3);
			points[index].set_x(stod(x));
			points[index].set_y(stod(y));
			if (temp2Order.size() != tempOrder.size())tempOrder = tempOrder.substr(tempOrder.find(")") + 2);
			else {
				index++;
				x = tempOrder.substr(tempOrder.find("(") + 1, tempOrder.find(",") - 1);
				y = tempOrder.substr(tempOrder.find(",") + 1, tempOrder.find(")") - 3);
				points[index].set_x(stod(x));
				points[index].set_y(stod(y));
				break;
			}
			index++;
		} while (true);
		Neighbourhood newNeigh(points[0], points[1], points[2], points[3], nameOfNei);
		newNeigh.findBound();
		neibhd.push_back(newNeigh);
		cout << "Your request has been successfully completed" << endl;
		cout << "Press enter to continue...";
		cin.get();
	}
	else if (order.find("Add-P") != -1) {
		regex pattern("Add-P \\[([a-zA-Z_][a-zA-Z0-9_]*)\\]\\s+\\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");// adad ashari ro nemigire
		if (!regex_match(order, pattern))throw 0;
		string name = order.substr((order.find("[") + 1), (order.find("]") - order.find("[") - 1));
		string x = order.substr(order.find("(") + 1, (order.find(",") - order.find("(") - 1));
		string y = order.substr(order.find(",") + 1, (order.find(")") - order.find(",") - 1));
		Point point(stod(x), stod(y));
		AddMainBranchPizzeria(name, point, currTree);
	}
	else if (order.find("Add-Br") != -1) {
		regex pattern("Add-Br\\s+\\[([a-zA-Z_][a-zA-Z0-9_]*)\\]\\s+\\[([a-zA-Z_][a-zA-Z0-9_]*)\\]\\s+\\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");// adad ashari ro nemigire
		if (!regex_match(order, pattern))throw 0;
		string name = order.substr((order.find("[") + 1), (order.find("]") - order.find("[") - 1));
		order = order.substr(order.find("]") + 1);
		string mainBranchName = order.substr((order.find("[") + 1), (order.find("]") - order.find("[") - 1));
		string x = order.substr(order.find("(") + 1, (order.find(",") - order.find("(") - 1));
		string y = order.substr(order.find(",") + 1, (order.find(")") - order.find(",") - 1));
		Point point(stod(x), stod(y));
		AddBranchPizzeria(name,mainBranchName, point, currTree);
	}
	else if (order.find("Avail-P") != -1) {
		regex pattern("Avail-P -?\\d+(\\.\\d+)?\\s+\\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");
		if (!regex_match(order, pattern))throw 0;
		string radius = order.substr(order.find("P")+1, order.find("(") - order.find("P")-1);
		string x = order.substr(order.find("(") + 1, (order.find(",") - order.find("(") - 1));
		string y = order.substr(order.find(",") + 1, (order.find(")") - order.find(",") - 1));
		currTree.rangeSearch(stod(x), stod(y), stod(radius));
	}
	else if (order.find("Del-Br") != -1) {
		regex check("Del-Br \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");
		if (!regex_match(order, check))throw 0;
		string x = order.substr(8, order.find(",")-order.find("(")-1);
		string y = order.substr(order.find(",")+1, order.find(")") -order.find(",")-1);
		Point remvNode(stod(x), stod(y));
		deleteBranchPizzeria(remvNode, currTree);
	}
	else if (order.find("Near-P") != -1) {
		regex check("Near-P \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");
		if (!regex_match(order, check))throw 0;
		string x = order.substr(8, order.find(",") - order.find("(") - 1);
		string y = order.substr(order.find(",") + 1, order.find(")") - order.find(",") - 1);
		Point queryPoint(stod(x), stod(y));
		currTree.findNearestNeighHelper(queryPoint);
	}
	else if (order.find("List-Brs") != -1) {
		regex check("List-Brs \\[([a-zA-Z_][a-zA-Z0-9_]*)\\]");
		if (!regex_match(order, check))throw 0;
		string name = order.substr(order.find("[") + 1, order.find("]") - order.find("[")-1);
		currTree.prinSubBranchesTemp(name);
	}
	else if (order.find("List-P") != -1) {
		regex check("List-P \\[([a-zA-Z_][a-zA-Z0-9_]*)\\]");
		if (!regex_match(order, check))throw 0;
		string name = order.substr(order.find("[") + 1, order.find("]") - order.find("[") - 1);
		int index = hashTableOfMainNodes.search(name);
		vector<BasicNode*> list;
		auto it = find_if(neibhd.begin(), neibhd.end(), [&](auto p) {
			return p.getName() == name; });
		displayListOfPizzeriaInTheNeighbourhood(list, currTree, *it);
	}
	else if (order.find("Most-Brs") != -1)
	{
		regex check("Most-Brs");
		if (!regex_match(order, check))throw 0;
		currTree.mostBranches();
	}
	else if (order.find("Near-Br") != -1)
	{
		regex pattern("Near-Br \\[([a-zA-Z_][a-zA-Z0-9_]*)\\]\\s+\\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");// adad ashari ro nemigire
		if (!regex_match(order, pattern))throw 0;
		string mainName = order.substr((order.find("[") + 1), (order.find("]") - order.find("[") - 1));
		string x = order.substr(order.find("(") + 1, (order.find(",") - order.find("(") - 1));
		string y = order.substr(order.find(",") + 1, (order.find(")") - order.find(",") - 1));
		Point queryPoint(stod(x), stod(y));
		currTree.findNearestSubBranch(queryPoint, mainName);

	}
	else if (order.find("Undo") != -1) {
			regex pattern("Undo\\s+Time\\s*:\\s*\\d+\\s+Command\\s*:\\s*\\d+");
		if (!regex_match(order, pattern))throw 0;
		isNow = false;
		string time = order.substr(order.find(":") + 1, order.find("C") - order.find(":") - 1);
		order = order.substr(order.find("a"));
		string command = order.substr(order.find(":") + 1);
		undo(stoi(time), stoi(command), currTree);
	}
	else if (order.find("Redo") != -1)
	 {
	 regex pattern("Redo");
	 if (!regex_match(order, pattern))throw 0;
	 backToThePresent(currTree);
	}
	else throw 0;
}
//***************************************************************************
void AddMainBranchPizzeria(string name, Point p, TwoDTree& currTree) {
	if(hashTableOfMainNodes.search(name)!=-1)throw CustomException("There is a main branch of the pizzeria with this name.\nChoose another name");
	if (currTree.searchWithCoordinates(p.getX(), p.getY()) != nullptr) throw CustomException("There is another pizzeria in this area!");
	Node_MainPizza* newPizzeria = new Node_MainPizza(p, name);
	currTree.addMainBranch(newPizzeria);
	cout << "Your request has been successfully completed" << endl;
	cout << "Press enter to continue...";
	cin.get();
}
//***************************************************************************
void AddBranchPizzeria(string name,string mainBranchName, Point p, TwoDTree& currTree) {
	if (currTree.searchWithCoordinates(p.getX(), p.getY()) != nullptr) throw CustomException("There is another pizzeria in this area!");
	if(hashTableOfMainNodes.search(mainBranchName)==-1) throw CustomException("There is no main branch pizzeria with this name!");
	Node_SubPizza* newPizzeria = new Node_SubPizza(p, name,mainBranchName);
	currTree.addSubBranch(newPizzeria);
	currTree.updateSubBranchInVectorAndHash(mainBranchName, newPizzeria);
	cout << "Your request has been successfully completed" << endl;
	cout << "Press enter to continue...";
	cin.get();
}
//***************************************************************************
void deleteBranchPizzeria(Point p, TwoDTree& currTree) {
	BasicNode* findNode = currTree.searchWithCoordinates(p.getX(), p.getY());
	if (findNode == nullptr) throw CustomException("There isn't any pizzeria in this area!");
	if (typeid(*findNode) == typeid(Node_MainPizza))throw CustomException("The coordinates given belong to a main pizzeria branch, you cannot delete it");
	currTree.deleteNode(p);
	cout << "Your request has been successfully completed" << endl;
	cout << "Press enter to continue...";
	cin.get();
}
//*************************************************************************************
void displayListOfPizzeriaInTheNeighbourhood(vector<BasicNode*>& list,TwoDTree & currTree, Neighbourhood& nb) {
	currTree.listOfPizzeriasInTheNeighborhood(list, nb);
	for (int i = 0; i < list.size(); i++) {
		list[i]->print();
	}
}
//*************************************************************************************
void help(ConsoleColor textColor, int delayMillis) {
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor);	
	fstream inputFile("help.txt");
	if (!inputFile.is_open()) {
		throw CustomException("can not open the file...");
	}
	string text;
	int i = 1;
	while (getline(inputFile, text)) {
		SetConsoleTextAttribute(hConsole, ConsoleColor::White);
		cout << i << "- ";
		SetConsoleTextAttribute(hConsole, textColor);
		for (const char& c : text) {
			cout << c;
			Sleep(delayMillis);
		}
		cout << endl;
		i++;
	}
	SetConsoleTextAttribute(hConsole, ConsoleColor::White);
	cout << "Press enter to continue...";
	cin.get();
}
//**************************************************************************************
void undo(int time, int command, TwoDTree& currTree) {
	currTree.bulidTreeFromTree(hashTableOfTrees.getTreeWithKeyAndChainNumber(time, command));
}
//***************************************************************************************
void backToThePresent(TwoDTree& currTree) {
	currTree = hashTableOfTrees.backToPeresent();

	//^^^^^^^^ display current tree^^^^^^^^^^^^
	/*currTree.display(currTree.root);
	cout << "--------------------------------------------"<<endl;*/
}

