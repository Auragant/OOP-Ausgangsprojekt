/*****************************************************************//**
 * \file	Foreground_Object.h
 * \brief	Declaration of the Foreground_Object
 *
 * \author	Jan
 * \date	October 2022
 *********************************************************************/
#pragma once
#include "Gosu/Gosu.hpp"


#ifndef FOREGROUND_OBJECT_H_
#define FOREGROUND_OBJECT_H_

class Foreground_object
{
public:
	int get_position_x() const;					//Get x-Axis Position as Int Value
	void set_position_x(int new_position);		//Set x-Axis Position as Int Value
	int get_position_y() const;					//Get y-Axis Position as Int Value
	void set_position_y(int new_position);		//Set y-Axis Position as Int Value
	Gosu::Color get_color() const;				//Returns the GOSU-Color-Value of the object
	void set_color(int new_color);				//Set the new Color-Value of the Object
	Foreground_object();						//Standard Constructor
	Foreground_object(int new_x, int new_y);	//Position Constructor
	Foreground_object(int new_x, int new_y, int n_color, int n_speed);	//Full Constructor
private:
	int position_x;								//Position on the x-Axis
	int position_y;								//Position on the x-Axis
	Gosu::Color o_color;						//Color of the Object
	int movement_speed;							//Movement Speed of the Object. 0 for no Movement
};

#endif // !FOREGROUND_OBJECT_H_