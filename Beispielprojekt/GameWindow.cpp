#include "GameWindow.h"
#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

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
	draw_player();
}

void GameWindow::draw_player()
{
	player.update_player();
	graphics().draw_triangle(
		player.P1.get_x(), player.P1.get_y(), player.get_color(),
		player.P2.get_x(), player.P2.get_y(), player.get_color(),
		player.P3.get_x(), player.P3.get_y(), player.get_color(),
		player.get_ZPos());
}

void GameWindow::input_updater()
{
	if (input().down(KB_A) &&  !input().down(KB_D))
	{
		//Move Left
		//x--
	}
	else if (input().down(KB_D) && !input().down(KB_A))
	{
		//Move Right
		//x++
	}
}