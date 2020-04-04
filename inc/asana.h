#ifndef ASANA_H
#define ASANA_H

#include <string>
#include <list>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;


class Asana {
	private:
		string Token;
		bool Initialized;

	public:
		const string API_URL = "https://app.asana.com/api/1.0/";
		json MyTasks;
		json Projects;
		json Tasks;
		json UserInfo;
		json UserTaskList;
		string Breadcrumb;
		// Constructors
		Asana();
		Asana(string tk);
		// Methods
		void Initialize(string tk);
		void PrintToken();
		// Printers
		void PrintMyTasksInList();
		void PrintProjectsInList();
		void PrintProjectTasksInList();
		void PrintMyInfo();
		// Loaders
		list<string> GetHeaders();
		json GetUserInfo();
		json GetMyTasks();
		json GetProjects();
		json GetProjectTasks(int index);
		json GetProjectTasks(string gid);

};

#endif
