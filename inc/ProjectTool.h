#ifndef PROJECT_TOOL_H
#define PROJECT_TOOL_H

#include <string>
#include <list>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;


class ProjectTool {
	protected:
		string Token;
		bool Initialized;


	public:
        enum class TOOL_TYPE { ASANA, TRELLO, };

        TOOL_TYPE Tool;

		json MyTasks;
		json Projects;
		json Tasks;
		json UserInfo;
		json UserTaskList;
		string Breadcrumb;
		// Constructors
		ProjectTool(TOOL_TYPE);
		ProjectTool(string tk, TOOL_TYPE);
        virtual ~ProjectTool() {};
		// Methods
		virtual void Initialize(string tk);
		void PrintToken();
		// Printers
		virtual void PrintMyTasksInList();
    	virtual void PrintProjectsInList();
		virtual void PrintProjectTasksInList();
		virtual void PrintMyInfo();
		// Loaders
		virtual list<string> GetHeaders();
		virtual json GetUserInfo();
		virtual json GetMyTasks() { return json::parse("{}"); }
		virtual json GetProjects();
		virtual json GetProjectTasks(int index);
		virtual json GetProjectTasks(string gid);

};

#endif
