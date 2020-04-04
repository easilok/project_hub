#ifndef BODY_H
#define BODY_H

#include <string>
#include <list>
#include <curses.h>

class Body {
	public:
		std::list<std::string>* items;
		std::list<std::string>* keys;
		int Page;
		Body(std::string username, int topBarSize, int bottomBarSize);
		void Greating(std::list<std::string> * text);
		int ShowList(std::list<std::string> * text, int selected, int offset);
	private:
		const int GREATING_LINE_SPACING = 2;
		WINDOW * WinBody;
		std::string Username;
		int WinRowPos;
		int WinRows;
		int WinColPos;
		int WinCols;
		int TopBarSize;
		int BottomBarSize;
		int ItemSize;
		void CreateWindow();
		void Display();
};

#endif
