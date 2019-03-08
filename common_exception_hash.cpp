#include "exception_hash.h"
#include <string>


Hash_Error::Hash_Error(const std::string& msg): msg(msg){}

const char* Hash_Error::what() const throw() {
	return msg.c_str();
}

