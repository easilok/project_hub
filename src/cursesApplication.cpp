#include "../inc/cursesApplication.h"
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <curses.h>

using namespace std;
using json = nlohmann::json;

	/* asana.GetProjects(); */

	/* asana.GetProjectTasks(1); */

	/* cout << "JSON User Email: " << asana.UserInfo["email"] << endl; */

CursesApp::CursesApp() {
	asana.Initialize("1/1158915502756106:421a4f1f7ec674a995a3a8cf379fd92a");                                          
	asana.GetMyTasks();

	BottomKeys = {"1", "2", "3", "q"};
	BottomMenus = {"My Tasks", "Projects", "My Info", "Quit"};
	TopKeys = {"A", "S"};
	TopMenus = {"Asana", "Trello"};
	BodyGreating = {
		"Tasks Pending: " + to_string(asana.MyTasks.size()),
		"Late Tasks: n/a",
	};

	Curses_init();

	/* menuBottom = new BarMenu(&BottomKeys, &BottomMenus, BarMenu::Position::BOTTOM); */
	/* menuTop = new BarMenu(&TopKeys, &TopMenus, BarMenu::Position::TOP); */
	/* body = new Body(asana.UserInfo["name"].get<string>(), menuTop->MENU_HEIGHT, menuBottom->MENU_HEIGHT); */

}

CursesApp::~CursesApp() {
	/* delete body; */
	/* delete menuBottom; */
	/* delete menuTop; */
	/* Curses_end(); */
}

void CursesApp::Curses_init() {
	// ncurses start
	initscr();
	noecho();
	cbreak();
	curs_set(0);

	refresh();

}

void CursesApp::Curses_end() {
	endwin();
}

string CursesApp::ProjectTasksMenu(int index) {
	string choice = "0";
	string retVal = "0";
	bool keepGoing = true;

	if (index >= (int)asana.Projects.size()) {
		cout << "Invalid Project. Please choose again" << endl << endl;
		return retVal;
	} else {
		asana.GetProjectTasks(index);
		cout << "Showing Tasks for project " << asana.Projects[index]["name"] 
				 << ":" << endl << endl;
		asana.PrintProjectTasksInList();
	}

	while (keepGoing) {
		cout << "What can we do?" << endl;
		cout << "q. Back to Previous." << endl << endl;

		cout << "Please choose operation: " << endl;
		cin >> choice;
		if (choice == "q") {
			keepGoing = false;
		}

		if (keepGoing) {
			asana.PrintProjectTasksInList();
		}
	}

	return retVal;
}

string CursesApp::ProjectsMenu(void) {
	string choice = "0";
	string retVal = "0";
	bool keepGoing = true;

	while (keepGoing) {

		asana.PrintProjectsInList();

		cout << "What can we do?" << endl << endl;
		cout << "Select Project Index to view tasks" << endl;
		cout << "q. Back to Previous." << endl << endl;

		cout << "Please choose operation: " << endl;
		cin >> choice;
		if (choice == "q") {
			keepGoing = false;
			retVal = choice;
		} else {
			try {
				int i = stoi(choice);

				if ((i <= 0) || (i > (int)asana.Projects.size())) {
					cout << "Invalid Project. Please choose again" << endl << endl;
				} else {
					string subChoice = ProjectTasksMenu(i - 1);
				}

			} catch (std::invalid_argument const &e) {
					cout << "Invalid Project. Please choose again" << endl << endl;
			} catch (std::out_of_range const &e) {
					cout << "Invalid Project. Please choose again" << endl << endl;
			}
		}
	}

	return retVal;
}

void CursesApp::UserTasks() {
	asana.GetMyTasks();

	BodyList.clear();

	for (int i = 1; i <= (int)asana.MyTasks.size(); i++) {
		string tmp = to_string(i) + " :" + asana.MyTasks[i]["name"].get<string>();
		BodyList.push_back(tmp);
	}

}

void CursesApp::ProcessUserMenu(Body* body, char * choice) {

	int visibleRows = 0;

	switch (*choice) {
		case '1':
			UserTasks();
			visibleRows = body->ShowList(&BodyList, -1, 0);
			break;
		default:
			break;
	}
}

void CursesApp::Run(void) {

	BarMenu menuBottom = BarMenu(&BottomKeys, &BottomMenus, BarMenu::Position::BOTTOM);
	BarMenu menuTop = BarMenu(&TopKeys, &TopMenus, BarMenu::Position::TOP);
	Body body = Body(asana.UserInfo["name"].get<string>(), menuTop.MENU_HEIGHT, menuBottom.MENU_HEIGHT);

	body.Greating(&BodyGreating);

	bool exitProgram = false;

	while(!exitProgram) {
		menuTop.Display();
		menuBottom.Display();
		char choice = getch();

		switch (choice) {
			case 'q':
				exitProgram = true;
				break;
			default:
				// Pass choice to menus and they should interact
				ProcessUserMenu(&body, &choice);
				break;
		}
	}

	Curses_end();
}

