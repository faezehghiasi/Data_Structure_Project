#pragma once
#include"Point.h"
using namespace std;
class Neighbourhood
{
private:
	Point p1;
	Point p2;
	Point p3;
	Point p4;
	string name;
	Point topLeft;
	Point bottomRight;
public:
	Neighbourhood(Point p1Val, Point p2Val, Point p3Val, Point p4Val,string Name);
	void findBound();
	bool isPointInsideNeighbourhood(const Point& point);
	Point getTopLeft();
	Point getBottomRight();
	string getName();
};

