#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <list>

using namespace std;


class Connection {
	private:

	public:
		// Constructors
		Connection();
		// Methods
		string GetWithHeaders(string url, list<string> header);
};

#endif
