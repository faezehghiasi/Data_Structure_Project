#include<iostream>
#include<string>
#include"BasicNode.h"
#include"Neighbourhood.h"
#include"Node_MainPizza.h"
#include"Node_SubPizza.h"
#include"Point.h"
#include"TwoDTree.h"
#include"UndoNode.h"
#include<stdlib.h>
#include<regex>
#include<string.h>
using namespace std;
void validCheck(string order, vector<Neighbourhood>& neibhd, TwoDTree& currTree, vector<pair<int, UndoNode>> hOTrees);
void AddBranchPizzeria(string name, string mainBranchName, Point p, TwoDTree& currTree);
void AddMainBranchPizzeria(string name, Point p, TwoDTree& currTree);
//************************************************************
int main(void) {
	string order;
	string currentOrder;
	int countOfOrder = 0;
	vector<Neighbourhood> Neighbourhoods;
	vector<pair<int,UndoNode>> hashOfTrees;
	TwoDTree currentTree;
	//*******************************************************
	while (true) {
		system("cls");
		cout << "\nEnter the command you want : (Enter Exit for end and Help to see order's form) : ";
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
				validCheck(currentOrder, Neighbourhoods, currentTree, hashOfTrees);
			}
			catch (int x)
			{
				cout << "Unvalid input!" << endl;
				cout << "Enter Help to show the commands..." << endl;
				cout << "Press enter to continue...";
				cin.get();
				break;
			}
			countOfOrder++;
			if(it!=-1)order = order.substr(it + 3);
		} while (it != -1);
	}
}
/*******************validation******************/
void validCheck(string order, vector<Neighbourhood>& neibhd, TwoDTree& currTree, vector<pair<int, UndoNode>> hOTrees) {
	//***** add neighbourhood *****
	if (order.find("Add-N") != -1) {
		//inja bakhsh regex kareh vase sadegi vorrodi
		regex check("Add-N \\[[a-z]+\\] \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\) \\(-?\\d+(\\.\\d+)?\\,-?\\d+(\\.\\d+)?\\)");
		if (!regex_match(order, check))throw 0;
		int locOfParentheses = order.find("(");
		Point points[4];
		string tempOrder, temp2Order;
		do {
			int i = 0;
			tempOrder = order.substr(locOfParentheses);
			temp2Order = tempOrder.substr(0, tempOrder.find(")"));
			string x, y;
			x = temp2Order.substr(temp2Order.find("(") + 1, temp2Order.find(",") - 1);
			y = temp2Order.substr(temp2Order.find(",") + 1, temp2Order.find(")") - 1);
			tempOrder = tempOrder.substr(tempOrder.find(")") + 2);
			points[i].set_x(stod(x));
			points[i].set_y(stod(y));
		} while (temp2Order.size() != tempOrder.size());
		Neighbourhood newNeigh(points[0], points[1], points[2], points[3]);
		neibhd.push_back(newNeigh);
		return;
	}
	else if (order.find("Add-P") != -1) {
		regex pattern("Add-P \\[([a-zA-Z_][a-zA-Z0-9_]*)\\]\\s*\\(\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*\\)");// adad ashari ro nemigire
		if (!regex_match(order, pattern))throw 0;
		string name = order.substr((order.find("[") + 1), (order.find("]") - order.find("[") - 1));
		string x = order.substr(order.find("(") + 1, (order.find(",") - order.find("(") - 1));
		string y = order.substr(order.find(",") + 1, (order.find(")") - order.find(",") - 1));
		Point point(stoi(x), stoi(y));
		AddMainBranchPizzeria(name, point, currTree);
	}
	else if (order.find("Add-Br") != -1) {
		regex pattern("^Add-Br\\s+\\[([a-zA-Z]+)\\]\\s+\\[([a-zA-Z]+)\\]\\s+\\((\\d+),(\\d+)\\)$");// adad ashari ro nemigire
		if (!regex_match(order, pattern))throw 0;
		string name = order.substr((order.find("[") + 1), (order.find("]") - order.find("[") - 1));
		order = order.substr(order.find("]") + 1);
		string mainBranchName = order.substr((order.find("[") + 1), (order.find("]") - order.find("[") - 1));
		string x = order.substr(order.find("(") + 1, (order.find(",") - order.find("(") - 1));
		string y = order.substr(order.find(",") + 1, (order.find(")") - order.find(",") - 1));
		Point point(stoi(x), stoi(y));
		AddBranchPizzeria(name,mainBranchName, point, currTree);
	}
}
//***************************************************************************
void AddMainBranchPizzeria(string name, Point p, TwoDTree& currTree) {
	Node_MainPizza* newPizzeria = new Node_MainPizza(p, name);
	currTree.addMainBranch(newPizzeria);
	// update hash function;
}
//***************************************************************************
void AddBranchPizzeria(string name,string mainBranchName, Point p, TwoDTree& currTree) {
	Node_SubPizza* newPizzeria = new Node_SubPizza(p, name,mainBranchName);
	currTree.addSubBranch(newPizzeria);
	// update hash function;
	// update tree
	// update vector
}
