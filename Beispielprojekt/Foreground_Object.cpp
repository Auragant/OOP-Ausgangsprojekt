﻿/*****************************************************************//**
 * \file   Foreground_Object.cpp
 * \brief  
 * 
 * \author Jan
 * \date   October 2022
 *********************************************************************/
#include "Foreground_Object.h"
//Definition of the Class

#pragma region Get/Set 
//Get x-Axis Position as int Value
int Foreground_object::get_position_x() const
{
	return position_x;
}
//Set x-Axis Position 
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
//Set y-Axis Position 
void Foreground_object::set_position_y(int new_position)
{
	position_y = new_position;
	return;
}
//Get the color of the object
Gosu::Color Foreground_object::get_color() const
{
	return o_color;
}
void Foreground_object::set_color(int new_Color)
{
	o_color = new_Color;
	return;
}
#pragma endregion

Foreground_object::Foreground_object()
{
	position_x = 100;
	position_y = 100;
	o_color = 0xFFFFFFFF;
	movement_speed = 0;
}

Foreground_object::Foreground_object(int new_x, int new_y)
{
	position_x = new_x;
	position_y = new_y;
	o_color = 0xFFFFFFFF;
	movement_speed = 0;
}

Foreground_object::Foreground_object(int new_x, int new_y, int n_color, int n_speed)
{
	position_x = new_x;
	position_y = new_y;
	o_color = n_color;
	movement_speed = n_speed;
}
