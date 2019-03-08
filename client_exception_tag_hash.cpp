#include "exception_tag_hash.h"
#include <string>


Tag_Hash_Error::Tag_Hash_Error(const std::string& msg): msg(msg){}

const char* Tag_Hash_Error::what() const throw() {
	return msg.c_str();
}

