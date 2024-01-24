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
public:
	Neighbourhood(Point p1Val, Point p2Val, Point p3Val, Point p4Val,string Name);
};

