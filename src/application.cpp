#include <application.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

	/* asana.GetProjects(); */

	/* asana.GetProjectTasks(1); */

	/* cout << "JSON User Email: " << asana.UserInfo["email"] << endl; */

App::App() {
	asana.Initialize("1/1158915502756106:421a4f1f7ec674a995a3a8cf379fd92a");                                          
}

string App::ProjectTasksMenu(int index) {
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

string App::ProjectsMenu(void) {
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

void App::Run (void) {

	string choice = "0";
	bool keepGoing = true;

	cout << "Welcome " << asana.UserInfo["name"] << endl << endl;

	while (keepGoing) {

		cout << "What can we do?" << endl << endl;

		cout << "1. Get My Tasks." << endl
				 << "2. Get Projects." << endl
				 << "3. Get My Info." << endl 
				 << "q. Quit." << endl << endl;

		cout << "Please choose operation: " << endl;
		cin >> choice;
		/* cin.clear(); */
		/* cin.get(); */
		if (choice == "1") {
			cout << "You chose \"My tasks\"" << endl << endl;
			asana.GetMyTasks();
			asana.PrintMyTasksInList();
			cout << endl;
		} else if (choice == "2") {
			cout << "You chose \"Projects\"" << endl << endl;
			asana.GetProjects();
			if (asana.Projects.empty()) {
				cout << "No projects in Workspace." << endl << endl;
			} else {
				ProjectsMenu();
			}
			cout << endl;
		} else if (choice == "3") {
			cout << "You chose \"My Info\"" << endl << endl;
			asana.PrintMyInfo();
			cout << endl;
		} else if (choice == "q") {
			cout << "You chose \"Quit\"" << endl << endl;
			keepGoing = false;
		} else {
			cout << "Invalid choice. Please choose again" << endl << endl;
		}
	}

	cout << "Bye......" << endl;

}
