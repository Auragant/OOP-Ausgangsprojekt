#include "GameWindow.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include "Game_Input.h"
using namespace Gosu;

void GameWindow::draw() {
	graphics().draw_line(
		10, 20, Gosu::Color::RED,
		200, 100, Gosu::Color::GREEN,
		0.0
	);
	return;
}

void GameWindow::update()
{
	Window::update();

	Game_Input instruction = input_updater();
	
	draw_player(instruction);
}

void GameWindow::draw_player(Game_Input instru)
{
	player.update_player(instru);
	graphics().draw_triangle(
		player.P1.get_x(), player.P1.get_y(), player.get_color(),
		player.P2.get_x(), player.P2.get_y(), player.get_color(),
		player.P3.get_x(), player.P3.get_y(), player.get_color(),
		player.get_ZPos());
}

Game_Input GameWindow::input_updater()
{
	Game_Input instru(0,0,0);

	if (input().down(KB_A) &&  !input().down(KB_D))
	{
		instru.Left = true;
	}
	else if (input().down(KB_D) && !input().down(KB_A))
	{
		instru.Right = true;
	}
	if (input().down(KB_SPACE))
	{
		instru.Shoot = true;
	}
	return instru;
}