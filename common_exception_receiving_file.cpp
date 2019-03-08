#include "exception_receiving_file.h"
#include <string>


Receiving_file_Error::Receiving_file_Error(const std::string& msg): msg(msg){}

const char* Receiving_file_Error::what() const throw() {
	return msg.c_str();
}

