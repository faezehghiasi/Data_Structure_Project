#pragma once
class Point {
	double x;
	double y;
public:
	Point(double xVal, double yVal) :x(xVal), y(yVal) {}
	friend class BasicNode;
};