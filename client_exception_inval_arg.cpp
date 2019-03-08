#include "exception_inval_arg.h"
#include <string>


Args_Error::Args_Error(const std::string& msg): msg(msg){}

const char* Args_Error::what() const throw() {
	return msg.c_str();
}

