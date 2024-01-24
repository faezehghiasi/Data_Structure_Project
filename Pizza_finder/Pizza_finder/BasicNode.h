#pragma once
#include<iostream>
#include<String>
#include"Point.h"
using namespace std;
class BasicNode {
	Point coordinates;
	BasicNode* left;
	BasicNode* right;
	string  name;
public:
	BasicNode(double xVal, double yVal, string nameVal) : coordinates(xVal, yVal), name(nameVal),left(nullptr),right(nullptr) {}
	BasicNode(Point p, string nameVal) : coordinates(p), name(nameVal), left(nullptr), right(nullptr) {}
	virtual void print(){};
	friend class TwoDTree;
};