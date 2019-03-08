#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#include "socket.h"
#include <string>



class Protocolo{
private:
	Socket* conexion;
public:
	/*Constructor: recibe la conexion para realizar los send y recv.*/
	explicit Protocolo(Socket* conexion);
	/*Envia segun el protocolo el nombre/string.*/
	void enviar_nombre(const char* nombre);
	/*Envia segun el protocolo el entero.*/
	void enviar_long(int longitud);
	/*Envia directamente la accion sin tratar endianess*/
	void enviar_accion(uint8_t respuesta); 
	/*Envia segun el protocolo el archivo*/
	void enviar_archivo(const char* nom_arch); 
	/*Recibe directamente la accion sin tratar endianess*/
	uint8_t recibir_accion(); 
	/*Recibe el entero*/
	int32_t recibir_long();	
	/*Recibe el nombre/string y devuelve un string con su contenido*/
	std::string recibir_nombre();
	/*Recibe el archivo, guardandolo en el directorio con el nombre pasado.*/
	void recibir_arch(std::string& nom_f_out);
};

#endif

