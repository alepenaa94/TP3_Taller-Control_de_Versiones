#ifndef OPEN_FILE_ERROR_H
#define OPEN_FILE_ERROR_H
#include <exception>
#include <string>

class Open_file_Error: public std::exception{
	private:
    	std::string msg;
	public:
		/*Defino el constructor de la excepcion*/
		explicit Open_file_Error(const std::string& msg);
		/*Defino el metodo what para mostrar el mensaje*/
		virtual const char* what() const throw();
};

#endif
