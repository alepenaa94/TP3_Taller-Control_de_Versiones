#include "exception_open_file.h"
#include <string>


Open_file_Error::Open_file_Error(const std::string& msg): msg(msg){}

const char* Open_file_Error::what() const throw() {
	return msg.c_str();
}

