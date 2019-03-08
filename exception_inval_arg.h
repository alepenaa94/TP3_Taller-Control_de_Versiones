#ifndef ARGS_ERROR_H
#define ARGS_ERROR_H
#include <exception>
#include <string>

class Args_Error: public std::exception{
	private:
    	std::string msg;
	public:
		/*Defino el constructor de la excepcion*/
		explicit Args_Error(const std::string& msg);
		/*Defino el metodo what para mostrar el mensaje*/
		virtual const char* what() const throw();
};

#endif
