/*******************************************************************
 * \file   Menu.h
 * \brief  Includes the Menu-Class as well as all defines and function declarations.
 * 
 * \author louis rosewich
 * \date   04.10.2022
 *******************************************************************/

#pragma once

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include "Foreground_Object.h"

#ifndef MENU_H_
#define MENU_H_

class Menu : public Window
{
public:

	Gosu::Image Logo;
	/*Menu_Window() : Window(800, 600, Logo("logo.png")
	{
		set_caption("Space Invaders");
	}
	*/
	double x = 0;
	double y = 0;

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		graphics().draw_line(
			10, 20, Gosu::Color::RED,
			200, 100, Gosu::Color::GREEN,
			0.0
		);

		Logo.draw_rot(x, y, 0.0, 0.0, 0.5, 0,5);
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
	}
};


#endif // !MENU_H

