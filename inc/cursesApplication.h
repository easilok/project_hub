#ifndef CURSES_APPLICATION_H
#define CURSES_APPLICATION_H

#include "asana.h"
#include "BarMenu.h"
#include "Body.h"

class CursesApp {
	public:
		CursesApp();
		~CursesApp();
		void Run (void);
		string ProjectsMenu(void);
		string ProjectTasksMenu(int index);
		void ProcessUserMenu(int * choice);

		enum class VISIBLE_MENU {
			GREETING,
			USER_INFO,
			MY_TASKS,
			PROJECTS,
			PROJECT_TASKS,
		};
	private:
		Asana asana;

		Body * body;
		BarMenu * menuBottom;
		BarMenu * menuTop;

		list<string> BottomKeys;
		list<string> BottomMenus;
		list<string> TopKeys;
		list<string> TopMenus;
		list<string> BodyGreeting;
		list<string> BodyList;

		int SelectedListItem;

		VISIBLE_MENU VisibleMenu;

		void Curses_init();
		void Curses_end();

		void UserTasks();
		void Projects();
		void ProjectTasks(int index);

};

#endif
