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
