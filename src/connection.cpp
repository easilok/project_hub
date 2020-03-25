#include <iostream>
#include <sstream>
#include "connection.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

using namespace std;

Connection::Connection() {}

string Connection::GetWithHeaders(string url, list<string> header) {

	try {
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		// Setting the URL to retrive.
		request.setOpt(new curlpp::options::Url(url));
		
		// Setting headers
    request.setOpt(new curlpp::options::HttpHeader(header)); 

		// Set output stream
		std::ostringstream response;
		request.setOpt(new curlpp::options::WriteStream(&response));

		request.perform();

		return string(response.str());

	}
	catch (curlpp::LogicError & e) {
		cout << e.what() << endl;
	}
	catch (curlpp::RuntimeError & e) {
		cout << e.what() << endl;
	}

	return "{}";

}
