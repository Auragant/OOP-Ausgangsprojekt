#pragma once
#include <Gosu/Gosu.hpp>
#include "Player_Object.h"
using namespace Gosu;

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

class GameWindow : public Window
{
public:

	GameWindow() : Window(800, 600)
	{
		set_caption("Space Invaders");
	}

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override;
	

	// Wird 60x pro Sekunde aufgerufen
	void update() override;

	void draw_player(Game_Input instru);
	Game_Input input_updater();
private:
	Player_Object player = Player_Object(100,400,0xFFFFFF, 2);

};

#endif //GAMEWINDOW_H_
