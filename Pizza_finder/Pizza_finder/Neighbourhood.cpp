#include "Neighbourhood.h"
using namespace std;
Neighbourhood::Neighbourhood(Point p1Val, Point p2Val, Point p3Val, Point p4Val,string Name) {
	this->p1 = p1Val;
	this->p2 = p2Val;
	this->p3 = p3Val;
	this->p4 = p4Val;
	this->name = Name;
}
//****************************************************************************
void Neighbourhood::findBound() {
	topLeft.x = min(min(p1.x, p2.x), min(p3.x, p4.x));
	topLeft.y = max(max(p1.y, p2.y), max(p3.y, p4.y));
	bottomRight.x = max(max(p1.x, p2.x), max(p3.x, p4.x));
	bottomRight.y = min(min(p1.y, p2.y), min(p3.y, p4.y));
}
//****************************************************************************
bool Neighbourhood::isPointInsideNeighbourhood(const Point& point) {
	return (point.x >= topLeft.x && point.x <= bottomRight.x &&
		point.y >= bottomRight.y && point.y <= topLeft.y);
}
//****************************************************************************
Point Neighbourhood::getTopLeft() { return topLeft; }
//****************************************************************************
Point Neighbourhood::getBottomRight() { return bottomRight; }
//*****************************************************************************
string Neighbourhood::getName() { return name; }