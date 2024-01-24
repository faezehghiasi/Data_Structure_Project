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
			temp2Order = tempOrder.substr(0,tempOrder.find(")"));
			string x, y;
			x = temp2Order.substr(temp2Order.find("(")+1, temp2Order.find(",") - 1);
			y= temp2Order.substr(temp2Order.find(",") + 1, temp2Order.find(")") - 1);
			tempOrder = tempOrder.substr(tempOrder.find(")") + 2);
			points[i].set_x(stod(x));
			points[i].set_y(stod(y));
		} while (temp2Order.size()!=tempOrder.size());
		Neighbourhood newNeigh(points[0], points[1], points[2], points[3]);
		neibhd.push_back(newNeigh);
		return;
		
	}
}
//************************************************************
int main(void) {
	string order;
	string currentOrder;
	int countOfOrder=0;
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
		if (order == "Help") {
			cout << "You should enter coordinates like (x,y)" << endl;
			cout << "You should enter names in brackets : [name]" << endl;
			cout << "\nPress enter to continue";
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
				cout << "\nPress enter to continue";
				cin.get();
				break;
			}
			countOfOrder++;
			if(it!=-1)order = order.substr(it + 3);
		} while (it != -1);
		
		
		
	}
}