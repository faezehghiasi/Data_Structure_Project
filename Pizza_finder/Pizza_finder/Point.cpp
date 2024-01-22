#include "Point.h"
Point& Point::operator =(const Point& p) {
	this->x = p.x;
	this->y = p.y;
	return *this;
}
