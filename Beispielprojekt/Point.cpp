#include "Point.h"

double Point::get_x()
{
	return pX;
}
double Point::get_y()
{
	return pY;
}
void Point::set_Point(auto x, auto y)
{
	pX = x;
	pY = y;
}

Point::Point()
{
	return;
}

Point::Point(double x, double y)
{
	pX = x;
	pY = y;
}
