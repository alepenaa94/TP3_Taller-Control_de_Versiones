#ifndef TAG_ERROR_H
#define TAG_ERROR_H
#include <exception>
#include <string>

class Tag_Error: public std::exception{
	private:
    	std::string msg;
	public:
		/*Defino el constructor de la excepcion*/
		explicit Tag_Error(const std::string& msg);
		/*Defino el metodo what para mostrar el mensaje*/
		virtual const char* what() const throw();
};

#endif
