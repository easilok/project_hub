#include "../inc/BarMenu.h"

using namespace std;

BarMenu::BarMenu(list<string> * k, list<string> * v, Position position) {

	if (k->size() < v->size()) {
		exit(EXIT_FAILURE);	
	}

	items = v;
	keys = k;
	BarPosition = position;
	
	CreateWindow();

}

void BarMenu::CreateWindow() {
	//
	// replace with size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	ItemSize = xMax / items->size();

	// calculate bar position
	int yPos = 0;
	if (BarPosition == Position::BOTTOM) {
		yPos = yMax - MENU_HEIGHT;
	}

	Menu = newwin(MENU_HEIGHT, xMax, yPos, 0);
	box(Menu, 0, 0);

}

void BarMenu::Display() {

	list<string>::iterator itItems = items->begin();
	list<string>::iterator itKeys = keys->begin();

	// Move cursor to the initial position
	wmove(Menu, 1, 1);

	for (int i = 0; i < (int)items->size(); i++) {
		// Prepare menu identification
		std::string tmp = *itKeys + ": " + *itItems;

		int textXpos = 1;

		if ((int)tmp.length() < ItemSize) {
			textXpos = (ItemSize - (int)tmp.length()) / 2;
		}

		wmove(Menu, 1, textXpos + (i * ItemSize)); 
		wprintw(Menu, tmp.c_str());

		wmove(Menu, 1, (i + 1) * ItemSize);
		// Don't print the separator in the last item
		if (i < (int)items->size() - 1) {
			wprintw(Menu, "|");
		}

		itItems++;
		itKeys++;
	}
	wrefresh(Menu);

}


