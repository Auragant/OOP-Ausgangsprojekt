#pragma once
#include "Foreground_Object.h"
#include "string.h"

//Declaration of Player_Object 

class Player_Object : public virtual Foreground_object
{
public:
	void draw_player(); //Just for the display of the Player
	void update_player(); //Cyclic update of Player
	void collision_detection();
	Player_Object(int pos_x, int pos_y, int color, int speed)
	{
		set_color(color);
		
	}
private:
	int hitPoints;
	int damage;
	int multiplier; //Is a Multiplier needed for anything?

};
