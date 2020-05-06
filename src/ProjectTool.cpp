#include <iostream>
#include "ProjectTool.h"
using namespace std;

ProjectTool::ProjectTool(TOOL_TYPE tool) {
	Token = "";
    Tool = tool;
	Initialized = false;
}

ProjectTool::ProjectTool(string tk, TOOL_TYPE tool) {
	Token = tk;
    Tool = tool;
}

void ProjectTool::Initialize(string tk) 
{ 
    Token = tk;
}

list<string> ProjectTool::GetHeaders() {
    list<string> header;
    header.push_back("");
    return header;
}

json ProjectTool::GetUserInfo() {
	return json::parse("{}");
}

void ProjectTool::PrintMyInfo() { }

/* json ProjectTool::GetMyTasks() { */
/* 	return json::parse("{}"); */
/* } */

void ProjectTool::PrintMyTasksInList() { }

json ProjectTool::GetProjects() {
	return json::parse("{}");
}

void ProjectTool::PrintProjectsInList() { }

json ProjectTool::GetProjectTasks(int index) {
	return json::parse("{}");
}

json ProjectTool::GetProjectTasks(string gid) {
	return json::parse("{}");
}

void ProjectTool::PrintProjectTasksInList() { }

