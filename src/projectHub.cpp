#include <iostream>
#include <application.h>
#include <curses.h>

using namespace std;

void curses_init();
void curses_end();

int main() {

	curses_init();

	App app = App();

	/* app.Run(); */
	app.RunWithCurses();

	curses_end();

	return 0;
}

void curses_init() {
	// ncurses start
	initscr();
	noecho();
	cbreak();
	curs_set(0);

}

void curses_end() {
	endwin();
}
