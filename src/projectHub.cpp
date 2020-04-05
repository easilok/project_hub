#include <iostream>
#include "../inc/application.h"
#include "../inc/cursesApplication.h"
#include <curses.h>

using namespace std;

int main() {

	setlocale(LC_ALL, "");

	/* App app = App(); */
	CursesApp app = CursesApp();

	app.Run();

	return 0;
}

