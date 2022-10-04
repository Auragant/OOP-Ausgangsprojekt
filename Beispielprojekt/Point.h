#pragma once

#ifndef POINT_H_
#define POINT_H_

/*
 * Simple Structure to describe points in our game
 * Not commented
 */
class Point
{
public:
	double get_x();
	double get_y();
	void set_Point(auto x, auto y);
	Point();
	Point(double x, double y);
private:
	double pX;
	double pY;
};

#endif // !POINT_H_