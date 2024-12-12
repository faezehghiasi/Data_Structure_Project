#pragma once
#include<iostream>
class Point {
	double x;
	double y;
public:
	Point(){}
	Point(double xVal, double yVal) :x(xVal), y(yVal) {}
	Point& operator =(const Point& p);
	void set_x(double xVal);
	void set_y(double yVal);
	double distanceSquared(Point);
	bool operator==(Point);
	double getX();
	double getY();
	friend class BasicNode;
	friend class TwoDTree;
	friend class Neighbourhood;
	friend class Node_SubPizza;
	friend class Node_MainPizza;
};