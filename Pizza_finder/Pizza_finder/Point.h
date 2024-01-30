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
	void set_x(double xVal);
	void set_y(double yVal);
	double distanceSquared(Point);
	bool operator==(Point);
};