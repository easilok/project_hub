#ifndef BAR_MENU_H
#define BAR_MENU_H

#include <string>
#include <list>
#include <curses.h>

class BarMenu {
	public:
		enum class Position { TOP, BOTTOM};

		Position BarPosition;

		const int MENU_HEIGHT = 3;
		std::list<std::string>* items;
		std::list<std::string>* keys;
		BarMenu(std::list<std::string> * k, std::list<std::string> * v, Position position);
		void display();
	private:
		WINDOW * Menu;

};

#endif
