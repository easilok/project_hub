#include <iostream>
#include "ProjectTool.h"
using namespace std;

ProjectTool::ProjectTool(TOOL_TYPE tool) {
	Token = "";
    Tool = tool;
	Initialized = false;
}

ProjectTool::ProjectTool(string tk, TOOL_TYPE tool) {
    Tool = tool;
	Initialize(tk);
}

void ProjectTool::Initialize(string tk) {
	Token = tk;
	GetUserInfo();
	Initialized = false;
	if (UserInfo != nlohmann::detail::value_t::null) {
		Initialized = true;
	}
}

list<string> ProjectTool::GetHeaders() {
    list<string> header;
    header.push_back("");
    return header;
}

json ProjectTool::GetUserInfo() {
	return json::parse("{}");
}

void ProjectTool::PrintMyInfo() {
    return;
}

json ProjectTool::GetMyTasks() {
	return json::parse("{}");
}

void ProjectTool::PrintMyTasksInList() {
    return;
}

json ProjectTool::GetProjects() {
	return json::parse("{}");
}

void ProjectTool::PrintProjectsInList() {
    return;
}

json ProjectTool::GetProjectTasks(int index) {
	return json::parse("{}");
}

json ProjectTool::GetProjectTasks(string gid) {
	return json::parse("{}");
}

void ProjectTool::PrintProjectTasksInList() {
    return;
}

