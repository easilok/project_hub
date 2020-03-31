#include "../inc/BarMenu.h"

using namespace std;

BarMenu::BarMenu(list<string> * k, list<string> * v, Position position) {

	if (k->size() < v->size()) {
		exit(EXIT_FAILURE);	
	}

	items = v;
	keys = k;
	BarPosition = position;

	// replace with size
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);

	// calculate bar position
	int yPos = 0;
	if (BarPosition == Position::BOTTOM) {
		yPos = yMax - MENU_HEIGHT;
	}

	Menu = newwin(MENU_HEIGHT, xMax, yPos, 0);
	box(Menu, 0, 0);

}

void BarMenu::display() {

	list<string>::iterator itItems = items->begin();
	list<string>::iterator itKeys = keys->begin();

	// Move cursor to the initial position
	wmove(Menu, 1, 1);

	for (int i = 0; i < (int)items->size(); i++) {
		// Prepare menu identification
		std::string tmp = *itKeys + ": " + *itItems;

		wprintw(Menu, tmp.c_str());
		wprintw(Menu, "   |   ");

		/* mvwprintw(Menu, i + 1, 1, tmp.c_str()); */

		itItems++;
		itKeys++;
	}
	wrefresh(Menu);

}


