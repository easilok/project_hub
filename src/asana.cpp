#include <iostream>
#include <sstream>
#include "asana.h"
#include "connection.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

using namespace std;

Asana::Asana(string tk):ProjectTool(tk, TOOL_TYPE::ASANA) {
    Initialize(tk);
}

void Asana::Initialize(string tk) {
    Token = tk;
    Initialized = true;
	GetUserInfo();
	if (UserInfo == nlohmann::detail::value_t::null) {
		Initialized = false;
	}
}

list<string> Asana::GetHeaders() {
		list<string> header; 
		header.push_back("Authorization: Bearer " + Token);
		header.push_back("Content-Type: application/json");
		header.push_back("Accept: application/json");

		return header;
}

json Asana::GetUserInfo() {

	UserInfo = json::parse("{}");

    if (!Initialized) {
        return UserInfo;
    }

	try {
		string url = API_URL + "users/me";

		Connection con = Connection();

		string response = con.GetWithHeaders(url, GetHeaders());

#ifdef DEBUG
		cout << "Debug - Asana::GetUserInfo - Response: " << response << endl;
#endif

		UserInfo = json::parse(response);

		if (UserInfo["data"] != nlohmann::detail::value_t::null) {
			UserInfo = UserInfo["data"];
		}
	}
	catch (curlpp::LogicError & e) {
		cout << e.what() << endl;
	}
	catch (curlpp::RuntimeError & e) {
		cout << e.what() << endl;
	}
	return UserInfo;
}

void Asana::PrintMyInfo() {
	if (UserInfo.empty()) {
		return;
	}

	GetMyTasks();

	cout << "Name: " << UserInfo["name"] << endl;
	cout << "Email: " << UserInfo["email"] << endl;

	if (!MyTasks.empty()) {
			cout << "Pending Tasks: ";
		if (MyTasks.is_array()) {
			cout << MyTasks.size() << endl;
		} else {
			cout << "1" << endl;
		}
	}
}

json Asana::GetMyTasks() {

	// Initialize Values
	UserTaskList = json::parse("{}");
	MyTasks = json::parse("{}");

	// If failed to initialized return empty
	if (!Initialized) {
		return MyTasks;
	}

	try {
		// Get Users Task Lists
		// GET /users/{user_gid}/user_task_list?workspace={workspace_gid}
		string url = API_URL + "users/" \
								 + UserInfo["gid"].get<string>() + "/user_task_list" \
								 + "?workspace=" + UserInfo["workspaces"][0]["gid"].get<string>();

		Connection con = Connection();

		string response = con.GetWithHeaders(url, GetHeaders());

#ifdef DEBUG
		cout << "Debug - Asana::GetUserTaskList - Response: " << response << endl;
#endif

		// Extract Data
		UserTaskList = json::parse(response);

		if (UserTaskList["data"] != nlohmann::detail::value_t::null) {
			UserTaskList = UserTaskList["data"];
		} else {
			// If get empty data return
			return MyTasks;
		}

		// Get Users Tasks
		// GET /user_task_list/{user_task_list_gid}/tasks
		url = API_URL + "user_task_lists/" \
				 + UserTaskList["gid"].get<string>() + "/tasks"\
				 + "?completed_since=now&opt_fields=name,assignee_status";

		response = con.GetWithHeaders(url, GetHeaders());

#ifdef DEBUG
		cout << "Debug - Asana::GetMyTasks - Response: " << response << endl;
#endif

		// Extract Data
		MyTasks = json::parse(response);

		if (MyTasks["data"] != nlohmann::detail::value_t::null) {
			MyTasks = MyTasks["data"];
		}
	}
	catch (curlpp::LogicError & e) {
		cout << e.what() << endl;
	}
	catch (curlpp::RuntimeError & e) {
		cout << e.what() << endl;
	}
	return UserInfo;
}

void Asana::PrintMyTasksInList() {
	if (MyTasks.empty()) {
		return;
	}


	if (MyTasks.is_array()) {
		for (int i = 0; i < (int)MyTasks.size(); i++) {
			cout << i + 1 << ". " << MyTasks[i]["name"] << endl;
		}

	} else {
		cout << "1. " << MyTasks["name"] << endl;
	}

}

json Asana::GetProjects() {

	Projects = json::parse("{}");

	try {
		string url = API_URL + "projects"\
								 + "?workspace=" + UserInfo["workspaces"][0]["gid"].get<string>();

		Connection con = Connection();

		string response = con.GetWithHeaders(url, GetHeaders());

#ifdef DEBUG
		cout << "Debug - Asana::GetProjects - Response: " << response << endl;
#endif

		Projects = json::parse(response);

		if (Projects["data"] != nlohmann::detail::value_t::null) {
			Projects = Projects["data"];
		}
	}
	catch (curlpp::LogicError & e) {
		cout << e.what() << endl;
	}
	catch (curlpp::RuntimeError & e) {
		cout << e.what() << endl;
	}
	return Projects;
}

void Asana::PrintProjectsInList() {
	if (Projects.empty()) {
		return;
	}


	if (Projects.is_array()) {
		for (int i = 0; i < (int)Projects.size(); i++) {
			cout << i + 1 << ". " << Projects[i]["name"] << endl;
		}

	} else {
		cout << "1. " << Projects["name"] << endl;
	}

}

json Asana::GetProjectTasks(int index) {
	Tasks = json::parse("{}");

	if (!Initialized) {
		return Tasks;
	}

	if ((index < 0) || (index >= (int)Projects.size())){
		return Tasks;
	}

	return GetProjectTasks(Projects[index]["gid"].get<string>());
}

json Asana::GetProjectTasks(string gid) {

	Tasks = json::parse("{}");

	if (!Initialized) {
		return Tasks;
	}

	try {
		string url = API_URL + "projects"\
								 + "/" + gid + "/tasks";

		Connection con = Connection();

		string response = con.GetWithHeaders(url, GetHeaders());

#ifdef DEBUG
		cout << "Debug - Asana::GetProjectTasks - Response: " << response << endl;
#endif

		Tasks = json::parse(response);

		if (Tasks["data"] != nlohmann::detail::value_t::null) {
			Tasks = Tasks["data"];
		}
	}
	catch (curlpp::LogicError & e) {
		cout << e.what() << endl;
	}
	catch (curlpp::RuntimeError & e) {
		cout << e.what() << endl;
	}
	return Tasks;
}

void Asana::PrintProjectTasksInList() {
	if (Tasks.empty()) {
		return;
	}


	if (Tasks.is_array()) {
		for (int i = 0; i < (int)Tasks.size(); i++) {
			cout << i + 1 << ". " << Tasks[i]["name"] << endl;
		}

	} else {
		cout << "1. " << Tasks["name"] << endl;
	}
}
