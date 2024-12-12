#include "Point.h"
Point& Point::operator =(const Point& p) {
	this->x = p.x;
	this->y = p.y;
	return *this;
}
void Point::set_x(double xVal) {
	this->x = xVal;
}
void Point::set_y(double yVal) {
	this->y = yVal;
}
bool Point::operator==(Point p) {
	if (this->x == p.x and this->y == p.y)return true;
	return false;
}
double Point::distanceSquared(Point other) {
	return pow(x - other.x, 2) + pow(y - other.y, 2);
}
double Point::getX() { return x; }
double Point::getY() { return y; }
