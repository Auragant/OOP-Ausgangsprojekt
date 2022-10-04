#pragma once
#include "Foreground_Object.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include "Point.h"
#include "Border.h"

#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

//Declaration of Player_Object

class Player_Object : public virtual Foreground_object
{
public:
	void draw_player();			//Just for the display of the Player
	void update_player();				//Cyclic update of Player
	void update_position();
	Border math_to_border();				// *This function should return the borders of the Player-Object as 4 integers
	void math_to_points();				//Giving the significant points.
	int get_HP();
	void set_HP(int nHP);
	int get_DMG();
	void set_DMG(int nDMG);
	int get_MP();
	void set_MP(int nMP);
	int get_SHP();
	void set_SHP(int nSHP);
	int get_SiX();
	void set_SiX(int nSiX);
	int get_SiY();
	void set_SiY(int nSiY);
	Player_Object(int pos_x, int pos_y, int color, int speed);
	Player_Object(int pos_x, int pos_y, int color, int speed, int HP, int DMG, int MP);
	Player_Object(int pos_x, int pos_y, int color, int speed, int HP, int DMG, int MP, int SHP, int SX, int SY);
private:
	int hitPoints = 3;
	int damage = 1;
	int multiplier = 1; //Is a Multiplier needed for anything?
	int shape = 1;		//Shape is a special function, x <= 0 -> image ; x = 1 -> triangle
	int sizeX = 10;		//Size in X-Dimension
	int sizeY = 10;		//Size in Y-Dimension
	int ZPos = 5;		//Layer of Gosu - Not meant to be changed...
	Point P1;
	Point P2;
	Point P3;
	Border localBorder;
};

#endif // !PLAYER_OBJECT_H_



