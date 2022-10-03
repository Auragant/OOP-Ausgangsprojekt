#include "Player_Object.h"
using namespace Gosu;
//Definition of Player_Object

/*
 * This Function draw_Player should draw the player_object
 * SHP describes the Shape of the Player.
 * x <= 0 -> image
 * x = 1 -> triangle
 * x > 1 -> quad
 */
void Player_Object::draw_player(int SHP)
{
	return;
}

/*
 * The update Function should be repeated with every frame.
 * Multi-Threading won't be a thing in this project for the first version
 */
void Player_Object::update_player()
{
	return;
}

/*
 *This function should return the borders of the Player-Object as 4 integers
 *Upper X (Up)
 *Lower X (Down)
 *Upper Y (Right)
 *Lower Y (Left)
 */
void Player_Object::math_to_border()
{
	return;
}

void Player_Object::math_to_points()
{
	
}

#pragma region GET/SET - DO NOT OPEN, unless necessary

/*
 * Get-Method for hitPoints
 */
int Player_Object::get_HP()
{
	return hitPoints;
}

/*
 * Set-Method for hitPoints
 */
void Player_Object::set_HP(int nHP)
{
	hitPoints = nHP;
}

/*
 * Get-Method for damage
 */
int Player_Object::get_DMG()
{
	return damage;
}

/*
 * Set-Method for damage
 */
void Player_Object::set_DMG(int nDMG)
{
	damage = nDMG;
}

/*
 * Get-Method for Multiplier
 */
int Player_Object::get_MP()
{
	return multiplier;
}

/*
 * Set-Method for Multiplier
 */
void Player_Object::set_MP(int nMP)
{
	multiplier = nMP;
}

/*
 * Get-Method for Shape
 */
int Player_Object::get_SHP()
{
	return shape;
}

/*
 * Set-Method for Shape
 */
void Player_Object::set_SHP(int nSHP)
{
	shape = nSHP;
}

/*
 * Get-Method for sizeX
 */
int Player_Object::get_SiX()
{
	return sizeX;
}

/*
 * Set-Method for sizeX
 */
void Player_Object::set_SiX(int nSiX)
{
	sizeX = nSiX;
}

/*
 * Get-Method for sizeY
 */
int Player_Object::get_SiY()
{
	return sizeY;
}

/*
 * Set-Method for sizeY
 */
void Player_Object::set_SiY(int nSiY)
{
	sizeY = nSiY;
}

#pragma endregion

/*
 * Constructor for a very basic Player_Object
 * Directly from Foreground_Object copied
 */
Player_Object::Player_Object(int pos_x, int pos_y, int color, int speed)
{
	Foreground_object(pos_x, pos_y, color, speed);
}

/*
 * Constructor for a Player_Object with HP, DMG and Multiplier
 */
Player_Object::Player_Object(int pos_x, int pos_y, int color, int speed, int HP, int DMG, int MP)
{
	Foreground_object(pos_x, pos_y, color, speed);
	hitPoints = HP;
	damage = DMG;
	multiplier = MP;
}

Player_Object::Player_Object(int pos_x, int pos_y, int color, int speed, int HP, int DMG, int MP, int SHP, int SX, int SY)
{
	Player_Object(pos_x, pos_y, color, speed, HP, DMG, MP);
	shape = SHP;
	sizeX = SX;
	sizeY = SY;
}