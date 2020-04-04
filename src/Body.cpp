#include "../inc/Body.h"

using namespace std;

Body::Body(string username, int topBarSize, int bottomBarSize) {

	TopBarSize = topBarSize;
	BottomBarSize = bottomBarSize;
	Username = username;

	CreateWindow();

}

void Body::CreateWindow() {
	
	// replace with size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// calculate body position
	WinColPos = 0;
	WinRowPos = 0;
	WinCols = xMax;
	WinRows = yMax - TopBarSize - BottomBarSize;
	WinRowPos = TopBarSize;

	WinBody = newwin(WinRows, WinCols, WinRowPos, WinColPos);
	box(WinBody, 0, 0);
	Display();

}

void Body::Greating(list<string> * text) {

	// Display Text Greatings
	// and all strings in list aligned vertically
	
	int firstStringRow = WinRows - (text->size() + 1) - (text->size() * GREATING_LINE_SPACING);
	firstStringRow /= 2;

	//Print Greating line
	string greating = "Welcome to Project Hub " + Username;
	int textStartCol = (WinCols - greating.length()) / 2;

	wmove(WinBody, firstStringRow, textStartCol);
	wprintw(WinBody, greating.c_str());

	list<string>::iterator itTexts = text->begin();

	for (int i = 0; i < (int)text->size(); i++) {
		textStartCol = (WinCols - (*itTexts).length()) / 2;

		wmove(WinBody, firstStringRow + (i + 1) * GREATING_LINE_SPACING, textStartCol);
		wprintw(WinBody, (*itTexts).c_str());

		itTexts++;

	}

	Display();

}

int Body::ShowList(list<string> * text, int selected, int offset) {

	int maxLines = WinRows / 2;	
	maxLines = (int)text->size() < maxLines ? (int)text->size() : maxLines;

	list<string>::iterator itText = text->begin();

	for (int i = 0; i < maxLines; i++) {
		
		if (i == selected) {
			//invert colors
		}

		wmove(WinBody, i * 2, 1);
		wprintw(WinBody, (*itText).c_str());

		itText++;
	}

	Display();

	return maxLines;
}

void Body::Display() {

	wrefresh(WinBody);

}

