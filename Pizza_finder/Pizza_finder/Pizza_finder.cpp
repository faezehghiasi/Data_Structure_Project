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
#pragma warning (disable:4996)
using namespace std;
void validCheck(string order, vector<Neighbourhood>& neibhd, TwoDTree& currTree);
void AddBranchPizzeria(string name, string mainBranchName, Point p, TwoDTree& currTree);
void AddMainBranchPizzeria(string name, Point p, TwoDTree& currTree);
//*****************************************************************************
int main(void) {
	int i = 0;
	HashTableOfTrees hashTableOfTrees;
	string order;
	string currentOrder;
	vector<Neighbourhood> Neighbourhoods;
	TwoDTree currentTree;
	//*************************************************************************
	while (true) {
		UndoList listOftrees;
		///system("cls");
		cout << "Enter the command you want : (Enter Exit for end and Help to see order's form) : ";
		getline(cin, order);
		//******************************************************
		if (order == "Exit")exit(1);
		if (order == "Help"||order =="help") {
			cout << "You should enter coordinates like (x,y)" << endl;
			cout << "You should enter names in brackets : [name]" << endl;
			cout << "Press enter to continue...";
			cin.get();
			continue;
		}
		//*********************************************************
		int it=0;
		do {
			it= order.find("&");
			currentOrder = order.substr(0, it - 1);
			try
			{
				validCheck(currentOrder, Neighbourhoods, currentTree);
			}
			catch (int x)
			{
				cout << "Unvalid input!" << endl;
				cout << "Enter Help to show the commands..." << endl;
				cout << "Press enter to continue...";
				cin.get();
				break;
			}
			UndoNode* newTree = new UndoNode(currentTree);
			listOftrees.pushBack(newTree);
			if(it!=-1)order = order.substr(it + 3);
		} while (it != -1);
		hashTableOfTrees.insert(listOftrees);
		for (int t = 0; t <= i; t++) {
			hashTableOfTrees.display(t);
			cout << "-----------------------------------------------------\n";
		}
		i++;
		cin.get();
	}

}
/*******************validation******************/
void validCheck(string order, vector<Neighbourhood>& neibhd, TwoDTree& currTree) {
	//***** add neighbourhood *****
	if (order.find("Add-N") != -1) {
		//inja bakhsh regex kareh vase sadegi vorrodi
		regex check("Add-N \\[[a-zA-Z]+\\] \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");
		if (!regex_match(order, check))throw 0;
		string nameOfNei = order.substr(order.find("[") + 1, order.find("]") - 7);
		int locOfParentheses = order.find("(");
		Point points[4];
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
		neibhd.push_back(newNeigh);
		return;

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
		regex pattern("^Add-Br\\s+\\[([a-zA-Z]+)\\]\\s+\\[([a-zA-Z]+)\\]\\s+\\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");// adad ashari ro nemigire
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

		getch();
	}
	else if (order.find("Del-Br") != -1) {
		regex check("Del-Br \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");
		if (!regex_match(order, check))throw 0;
		string x = order.substr(8, order.find(",")-order.find("(")-1);
		string y = order.substr(order.find(",")+1, order.find(")") -order.find(",")-1);
		Point remvNode(stod(x), stod(y));
		currTree.deleteNode(remvNode);
	}
	else if (order.find("Near-P") != -1) {
		regex check("Near-P \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");
		if (!regex_match(order, check))throw 0;
		string x = order.substr(8, order.find(",") - order.find("(") - 1);
		string y = order.substr(order.find(",") + 1, order.find(")") - order.find(",") - 1);
		Point queryPoint(stod(x), stod(y));
		currTree.findNearestNeighbourhood(queryPoint, true, currTree.getRoot());
	}
}
//***************************************************************************
void AddMainBranchPizzeria(string name, Point p, TwoDTree& currTree) {
	Node_MainPizza* newPizzeria = new Node_MainPizza(p, name);
	currTree.addMainBranch(newPizzeria);
	// update hash function;
	//error 
}
//***************************************************************************
void AddBranchPizzeria(string name,string mainBranchName, Point p, TwoDTree& currTree) {
	Node_SubPizza* newPizzeria = new Node_SubPizza(p, name,mainBranchName);
	currTree.addSubBranch(newPizzeria);
	// update hash function;
	// update tree
	// update vector
    // error
}
