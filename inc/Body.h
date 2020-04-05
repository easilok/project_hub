#ifndef BODY_H
#define BODY_H

#include <string>
#include <list>
#include <curses.h>

class Body {
	public:
		const static int GREETING_LINE_SPACING = 2;
		const static int COLUMN_PRINT_OFFSET = 3;
		const static int ROW_PRINT_OFFSET = 3;
		std::list<std::string>* items;
		std::list<std::string>* keys;
		int Page;
		Body(std::string username, int topBarSize, int bottomBarSize);
		void Greeting(std::list<std::string> * text);
		int ShowList(std::list<std::string> * text, int *selected, int offset);
	private:
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
		void Clear();
};

#endif
