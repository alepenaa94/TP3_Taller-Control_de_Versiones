#ifndef HASH_ERROR_H
#define HASH_ERROR_H
#include <exception>
#include <string>

class Hash_Error: public std::exception{
	private:
    	std::string msg;
	public:
		/*Defino el constructor de la excepcion*/
		explicit Hash_Error(const std::string& msg);
		/*Defino el metodo what para mostrar el mensaje*/
		virtual const char* what() const throw();
};

#endif
