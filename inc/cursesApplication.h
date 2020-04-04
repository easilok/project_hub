#ifndef CURSES_APPLICATION_H
#define CURSES_APPLICATION_H

#include "asana.h"
#include "BarMenu.h"
#include "Body.h"

class CursesApp {
	private:
		Asana asana;

		/* Body * body; */
		/* BarMenu * menuBottom; */
		/* BarMenu * menuTop; */

		list<string> BottomKeys;
		list<string> BottomMenus;
		list<string> TopKeys;
		list<string> TopMenus;
		list<string> BodyGreating;
		list<string> BodyList;

		void Curses_init();
		void Curses_end();

		void UserTasks();

	public:
		CursesApp();
		~CursesApp();
		void Run (void);
		string ProjectsMenu(void);
		string ProjectTasksMenu(int index);
		void ProcessUserMenu(Body * body, char * choice);
};

#endif
