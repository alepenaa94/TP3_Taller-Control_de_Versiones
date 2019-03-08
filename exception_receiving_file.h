#ifndef RECEIVING_FILE_ERROR_H
#define RECEIVING_FILE_ERROR_H
#include <exception>
#include <string>

class Receiving_file_Error: public std::exception{
	private:
    	std::string msg;
	public:
		/*Defino el constructor de la excepcion*/
		explicit Receiving_file_Error(const std::string& msg);
		/*Defino el metodo what para mostrar el mensaje*/
		virtual const char* what() const throw();
};

#endif
