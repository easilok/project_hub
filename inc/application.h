#ifndef APPLICATION_H
#define APPLICATION_H

#include <asana.h>

class App {
	private:
		Asana asana;

	public:
		App();
		void Run (void);
		string ProjectsMenu(void);
		string ProjectTasksMenu(int index);
};

#endif
