#ifndef ASANA_H
#define ASANA_H

#include <string>
#include <list>
#include "ProjectTool.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;


class Asana : public ProjectTool {
	private:

	public:
		const string API_URL = "https://app.asana.com/api/1.0/";
		// Constructors
		Asana():ProjectTool(TOOL_TYPE::ASANA) {}
		Asana(string tk):ProjectTool(tk, TOOL_TYPE::ASANA) {}
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
