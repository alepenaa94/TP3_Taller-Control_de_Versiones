#define _POSIX_C_SOURCE 200112L
#include <string>
#include "socket.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <bitset>
#include "exception_inval_arg.h"
#include "exception_open_file.h"
#include "exception_tag_hash.h"
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdlib.h>
#include "Protocolo.h"

#define CERO 0
#define RET_OK 0
#define VALID 1
#define CANT_ARG_VAL 5
#define COMANDO 3
#define ARG_PUERTO 2
#define ARG_IP 1
#define ARG_TAG 5
#define ARG_PULL 5
#define ARG_PUSH 6
#define ARG_NAME 4
#define ARG_HASH 5

bool es_digito(char* str){
	for (unsigned int i = CERO; i < strlen(str); i++){
		if(isdigit(str[i])==CERO){
			return false;
		}
	}
	return true;
}

int contar_hashes(int argc){
	return argc-5;
}

int cliente_tag_file(int argc, char *argv[],Protocolo& protocolo){
	protocolo.enviar_accion(2);
	protocolo.enviar_long(contar_hashes(argc));
	protocolo.enviar_nombre(argv[ARG_NAME]);
	for (int i = 5; i < argc; i++){
		protocolo.enviar_nombre(argv[i]);		
	}
	uint8_t respuesta = protocolo.recibir_accion();
	if(respuesta==CERO){
		throw Tag_Hash_Error("Error: tag/hash incorrecto.");
	}
	return RET_OK;
}

int cliente_pull_file(int argc, char *argv[],Protocolo& protocolo){
	protocolo.enviar_accion(3);
	protocolo.enviar_nombre(argv[ARG_NAME]);
	uint8_t respuesta = protocolo.recibir_accion();
	if(respuesta==CERO){
		throw Tag_Hash_Error("Error: tag/hash incorrecto.");
	}else{
		int32_t cantidad_arch = protocolo.recibir_long();
		for (int i = CERO; i < cantidad_arch; i++){
			std::string nombre_file;
			nombre_file = protocolo.recibir_nombre();
			nombre_file.append(".");
			nombre_file.append(argv[ARG_NAME]);
			protocolo.recibir_arch(nombre_file);
		}
	return RET_OK;
	}
}

int cliente_push_file(int argc, char *argv[],Protocolo& protocolo){
	protocolo.enviar_accion(1);
	protocolo.enviar_nombre(argv[ARG_NAME]);
	protocolo.enviar_nombre(argv[ARG_HASH]);
	uint8_t respuesta = protocolo.recibir_accion();
	if(respuesta==VALID){
		protocolo.enviar_archivo(argv[ARG_NAME]);
	}
	return RET_OK;
}

int	main(int argc, char *argv[]){
	try{
		if(argc < CANT_ARG_VAL){
			throw Args_Error("Error: argumentos invalidos.");
		}else{
			if(!es_digito(argv[ARG_PUERTO])){
				throw Args_Error("Error: argumentos invalidos.");
			}
			std::string puerto(argv[ARG_PUERTO]);
			std::string ip(argv[ARG_IP]);
			Socket clt(ip,puerto);
			Protocolo protocolo(&clt);
			if(strcmp(argv[COMANDO],"tag")==CERO && argc >ARG_TAG){
				return cliente_tag_file(argc,argv,protocolo);
			}else if (strcmp(argv[COMANDO],"push")==CERO && argc==ARG_PUSH){
				return cliente_push_file(argc,argv,protocolo);
			}else if (strcmp(argv[COMANDO],"pull")==CERO && argc==ARG_PULL){
				return cliente_pull_file(argc,argv,protocolo);
			}else{
				throw Args_Error("Error: argumentos invalidos.");
			}
		}
	}
	catch(const std::exception &e) {
		std::cout<< e.what() <<'\n';
		return RET_OK;
	}  
}


