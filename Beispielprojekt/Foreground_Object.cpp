#include "Foreground_Object.h"
//Definition of the Class

//Get x-Axis Position as int Value
int Foreground_object::get_position_x() const
{
	return position_x;
}

//Set x-Axis Position as int Value
void Foreground_object::set_position_x(int new_position)
{
	position_x = new_position;
	return;
}

//Get y-Axis Position as Int Value
int Foreground_object::get_position_y() const
{
	return position_y;
}
void Foreground_object::set_position_y(int new_position)
{
	position_y = new_position;
	return;
}
Gosu::Color Foreground_object::get_color() const
{
	return o_color;
}
void Foreground_object::set_color(Gosu::Color new_Color)
{
	o_color = new_Color;
	return;
}
Foreground_object::Foreground_object()
{
	position_x = 100;
	position_y = 100;
	o_color = 0xFFFFFFFF;
	movement_speed = 1;
}
