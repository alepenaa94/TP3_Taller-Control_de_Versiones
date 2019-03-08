#include "exception_tag.h"
#include <string>


Tag_Error::Tag_Error(const std::string& msg): msg(msg){}

const char* Tag_Error::what() const throw() {
	return msg.c_str();
}

