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
		Asana(string tk);
        // Methods
        void Initialize(string);
		// Printers
		void PrintMyTasksInList();
		void PrintProjectsInList();
		void PrintProjectTasksInList();
		void PrintMyInfo();
		// Loaders
		list<string> GetHeaders() override;
		json GetUserInfo() override;
		virtual json GetMyTasks() override;
		json GetProjects() override;
		json GetProjectTasks(int index) override;
		json GetProjectTasks(string gid) override;

};

#endif
