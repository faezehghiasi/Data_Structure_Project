#pragma once
#include<iostream>
class Point {
	double x;
	double y;
public:
	Point(){}
	Point(double xVal, double yVal) :x(xVal), y(yVal) {}
	Point& operator =(const Point& p);
	friend class BasicNode;
	friend class TwoDTree;
};