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

void Body::Greeting(list<string> * text) {

	// Display Text Greatings
	// and all strings in list aligned vertically
	
	int firstStringRow = WinRows - (text->size() + 1) - (text->size() * GREETING_LINE_SPACING);
	firstStringRow /= 2;

	//Print Greating line
	string greeting = "Welcome to Project Hub " + Username;
	int textStartCol = (WinCols - greeting.length()) / 2;

	wmove(WinBody, firstStringRow, textStartCol);
	wprintw(WinBody, greeting.c_str());

	list<string>::iterator itTexts = text->begin();

	for (int i = 0; i < (int)text->size(); i++) {
		textStartCol = (WinCols - (*itTexts).length()) / 2;

		wmove(WinBody, firstStringRow + (i + 1) * GREETING_LINE_SPACING, textStartCol);
		wprintw(WinBody, (*itTexts).c_str());

		itTexts++;

	}

	Display();

}

int Body::ShowList(list<string> * text, int * selected, int offset) {

	Clear();

	int maxLines = (WinRows - (2 * ROW_PRINT_OFFSET)) / 2;	
	maxLines = (int)text->size() < maxLines ? (int)text->size() : maxLines;

	list<string>::iterator itText = text->begin();

	if (*selected > maxLines - 1) {
		*selected = maxLines - 1;
	}

	for (int i = 0; i < maxLines; i++) {
		
		if (i == *selected) {
			//invert colors
			wattron(WinBody, A_REVERSE);
		}

		wmove(WinBody, ROW_PRINT_OFFSET + i * 2, COLUMN_PRINT_OFFSET);
		wprintw(WinBody, (*itText).c_str());
		wattroff(WinBody, A_REVERSE);

		itText++;
	}

	Display();

	return maxLines;
}

void Body::Clear() {

	wclear(WinBody);
	box(WinBody, 0, 0);

}

void Body::Display() {

	wrefresh(WinBody);

}

