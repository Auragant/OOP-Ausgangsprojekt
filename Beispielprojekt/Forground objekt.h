#pragma once
#include "Gosu/Gosu.hpp"
//Just declaration of the Class
class Forground_objekt
{
public:
	int get_position_x();						//Get x-Axis Position as Int Value
	void set_position_x(int new_position);		//Set x-Axis Position as Int Value
	int get_position_y();						//Get y-Axis Position as Int Value
	void set_position_y(int new_position);		//Set y-Axis Position as Int Value
	Gosu::Color get_color();					//Returns the GOSU-Color-Value of the object
	void set_color(Gosu::Color);				//Set the new Color-Value of the Object
private:
	int position_x;				//Position on the x-Axis
	int position_y;				//Position on the x-Axis
	Gosu::Color o_color;		//Color of the Object
	int movement_speed;			//Movement Speed of the Object. 0 for no Movement

};
