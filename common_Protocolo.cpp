#include "Protocolo.h"
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include "exception_open_file.h"
#include "exception_receiving_file.h"
#include <iostream>
#include <string>

#define BYTES_4 4
#define BYTE_1 1
#define CERO 0
#define INVALID -1
#define TAM_BUFF 100

Protocolo::Protocolo(Socket* conexion): conexion(conexion){
}


void Protocolo::enviar_nombre(const char* nombre){
	unsigned int longitud = strlen(nombre);
	this->enviar_long(longitud);
	conexion->enviar(nombre,longitud);
}

void Protocolo::enviar_long(int longitud){
	int32_t conv = htonl(longitud);
	conexion->enviar((const char*)&conv,BYTES_4);
}


void Protocolo::enviar_accion(uint8_t respuesta){
	conexion->enviar((const char*)&respuesta,BYTE_1);
}


void Protocolo::enviar_archivo(const char* nom_arch){
	std::ifstream my_file_read;
	my_file_read.open(nom_arch, std::ifstream::in);
	if(!my_file_read){
		this->enviar_long(INVALID); 
		throw Open_file_Error("Error: archivo inexistente.");
	}
	my_file_read.seekg(CERO, my_file_read.end);
	unsigned int longitud=my_file_read.tellg();
	my_file_read.seekg(CERO, my_file_read.beg);
	this->enviar_long(longitud);
	while(!my_file_read.eof()){
			char buff[TAM_BUFF];
			my_file_read.read(buff,TAM_BUFF); //esto ok?	
			conexion->enviar(buff,my_file_read.gcount());
	}
	my_file_read.close();
} 



uint8_t Protocolo::recibir_accion(){
	uint8_t respuesta;
	conexion->recibir((char*)&respuesta,BYTE_1);
	return respuesta;
}


int32_t Protocolo::recibir_long(){
	int32_t longt;
	conexion->recibir((char*)&longt,BYTES_4);
	return ntohl(longt);
}

std::string Protocolo::recibir_nombre(){
	int32_t longt = this->recibir_long();
	char* txt = (char*)malloc((sizeof(char)*longt)+1);
	conexion->recibir(txt,longt);
	txt[longt]='\0';
	std::string nombre(txt);
	free(txt);
	return nombre;
}
	


void Protocolo::recibir_arch(std::string& nom_f_out){
	int32_t largo_file = this->recibir_long(); //funciona esto??
	if(largo_file==-1){
		throw Receiving_file_Error("Error al recibir archivo.");
	}
	std::ofstream my_file(nom_f_out, std::ofstream::out);
	int recibido=CERO;
	bool socket_error=false;
	unsigned int cant_restante = largo_file;
	while(recibido!=largo_file && !socket_error){
		char buff[TAM_BUFF]; 
		unsigned int cant_a_leer = TAM_BUFF;
		if(TAM_BUFF>cant_restante){
			cant_a_leer = cant_restante;
		}
		int a =conexion->recibir(buff,cant_a_leer); //esto ok?
		if(a==INVALID){
			socket_error=true;
			break;
		}else if (a!=CERO){
			for (int i = CERO; i < a; i++){
				my_file<<buff[i];
			}
			recibido+=a;
		}
	}
	my_file.close();
}



