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
    /* Asana * asana; */
    /* Tools.push_back(Asana("1/1158915502756106:421a4f1f7ec674a995a3a8cf379fd92a")); */
    /* asana = &Tools[Tools.length - 1]; */
	asana.Initialize("1/1158915502756106:421a4f1f7ec674a995a3a8cf379fd92a");                                          
	asana.GetMyTasks();
    /* trello.Initialize("e8f3272462329692eca21f0d208ae202490e5315fcca6e0fef89f4afaa0913ed"); */

	BottomKeys = {"1", "2", "3", "q"};
	BottomMenus = {"My Tasks", "Projects", "My Info", "Quit"};
	TopKeys = {"A", "S"};
	TopMenus = {"Asana", "Trello"};
	BodyGreeting = {
		"Tasks Pending: " + to_string(asana.MyTasks.size()),
		"Late Tasks: n/a",
	};

	Curses_init();

	menuBottom = new BarMenu(&BottomKeys, &BottomMenus, BarMenu::Position::BOTTOM);
	menuTop = new BarMenu(&TopKeys, &TopMenus, BarMenu::Position::TOP);
	body = new Body(asana.UserInfo["name"].get<string>(), BarMenu::MENU_HEIGHT, BarMenu::MENU_HEIGHT);

}

CursesApp::~CursesApp() {
	delete body;
	delete menuBottom;
	delete menuTop;
	Curses_end();
}

void CursesApp::Curses_init() {
	// ncurses start
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);

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

	for (int i = 0; i < (int)asana.MyTasks.size(); i++) {
		string tmp = to_string(i + 1) + ": " + asana.MyTasks[i]["name"].get<string>();
		BodyList.push_back(tmp);
	}

}

void CursesApp::Projects() {

	asana.GetProjects();

	BodyList.clear();

	for (int i = 0; i < (int)asana.Projects.size(); i++) {
		string tmp = to_string(i + 1) + ": " + asana.Projects[i]["name"].get<string>();
		BodyList.push_back(tmp);
	}

}

void CursesApp::ProjectTasks(int index) {
	if ((index < 0) || (index >= (int)asana.Projects.size())) {
		return;
	}

	asana.GetProjectTasks(index);

	BodyList.clear();

	for (int i = 0; i < (int)asana.Tasks.size(); i++) {
		string tmp = to_string(i + 1) + ": " + asana.Tasks[i]["name"].get<string>();
		BodyList.push_back(tmp);
	}

}

void CursesApp::ProcessUserMenu(int * choice) {

	int visibleRows = 0;

	switch (*choice) {
		case '1':
			UserTasks();
			SelectedListItem = -1;
			visibleRows = body->ShowList(&BodyList, &SelectedListItem, 0);
			VisibleMenu = VISIBLE_MENU::MY_TASKS;
			break;
		case '2':
			Projects();
			SelectedListItem = -1;
			visibleRows = body->ShowList(&BodyList, &SelectedListItem, 0);
			VisibleMenu = VISIBLE_MENU::PROJECTS;
			break;
		case KEY_DOWN:
			SelectedListItem++;
			visibleRows = body->ShowList(&BodyList, &SelectedListItem, 0);
			break;
		case KEY_UP:
			if(--SelectedListItem < 0) {
				SelectedListItem = 0;
			}
			visibleRows = body->ShowList(&BodyList, &SelectedListItem, 0);
			break;
		case 10: // Enter
			if (VisibleMenu == VISIBLE_MENU::PROJECTS) {
				ProjectTasks(SelectedListItem);
				SelectedListItem = -1;
				visibleRows = body->ShowList(&BodyList, &SelectedListItem, 0);
				VisibleMenu = VISIBLE_MENU::PROJECT_TASKS;
			}
			break;
		default:
			break;
	}
}

void CursesApp::Run(void) {

	/* BarMenu menuBottom = BarMenu(&BottomKeys, &BottomMenus, BarMenu::Position::BOTTOM); */
	/* BarMenu menuTop = BarMenu(&TopKeys, &TopMenus, BarMenu::Position::TOP); */
	/* Body body = Body(asana.UserInfo["name"].get<string>(), BarMenu::MENU_HEIGHT, BarMenu::MENU_HEIGHT); */

	body->Greeting(&BodyGreeting);

	bool exitProgram = false;

	while(!exitProgram) {
		menuTop->Display();
		menuBottom->Display();
		int choice = getch();

		switch (choice) {
			case 'q':
				exitProgram = true;
				break;
			default:
				// Pass choice to menus and they should interact
				ProcessUserMenu(&choice);
				break;
		}
	}

}

