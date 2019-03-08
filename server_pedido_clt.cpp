#include "pedido_clt.h"
#include "sistema_de_version.h"
#include "socket.h"
#include <string>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include "Sincronizar.h"
#include <vector>
#include "exception_receiving_file.h"
#define COMANDO_TAG 2
#define COMANDO_PULL 3
#define COMANDO_PUSH 1
#define CERO 0
#define VALID 1




Pedido_clt::Pedido_clt(Socket* conexion,Sistema_de_version& sistema,
							std::mutex& m, Protocolo& protocolo):
	conexion(conexion), sistema(sistema), proceso_terminado(false),m(m),
	protocolo(protocolo){}


bool Pedido_clt::is_finish(){
	return proceso_terminado;
}


void Pedido_clt::run(){
	uint8_t comando= protocolo.recibir_accion();
	if(comando==COMANDO_TAG){
		this->proceso_tag();
	}else if (comando==COMANDO_PUSH){
		this->proceso_push();
	}else if (comando==COMANDO_PULL){
		this->proceso_pull();
	}else{
		proceso_terminado=true;
		return;
	}
}
	

// SIRVE? no conviene que al cerrar el server, cierre todas las conexiones??
Socket* Pedido_clt::get_conexion(){
	return conexion;
}


// NUEVO
void Pedido_clt::proceso_push(){
	std::string nombre_archivo;
	nombre_archivo = protocolo.recibir_nombre();
	std::string nombre_hash;
	nombre_hash = protocolo.recibir_nombre();
	Sincronizar sincronizar(m);
	if(!(sistema.push_valido(nombre_hash))){
		protocolo.enviar_accion(CERO);
	}else{
		protocolo.enviar_accion(VALID);
		try{
			protocolo.recibir_arch(nombre_hash);
		}
		catch(Receiving_file_Error& e) {
			proceso_terminado=true;
			return;
		}
		sistema.do_push(nombre_archivo,nombre_hash);
	}
	proceso_terminado=true;
}


// NUEVO
void Pedido_clt::proceso_pull(){
	std::string nombre_tag;
	nombre_tag = protocolo.recibir_nombre();

	Sincronizar sincronizar(m);
	if(!sistema.pull_valido(nombre_tag)){
		protocolo.enviar_accion(CERO);
	}else{
		protocolo.enviar_accion(VALID);
		std::vector<std::string> lista_hash = sistema.do_pull(nombre_tag);
		protocolo.enviar_long(lista_hash.size());
		for (unsigned int i = CERO; i < lista_hash.size(); i++){
			std::string nom_file;
			nom_file = sistema.get_hash(lista_hash[i]);
			protocolo.enviar_nombre(nom_file.c_str());
			protocolo.enviar_archivo(nom_file.c_str());
		}
	}
	proceso_terminado=true;
}


// NUEVO
void Pedido_clt::proceso_tag(){
	int32_t cantidad_hash = protocolo.recibir_long();
	std::string nom_tag;
	nom_tag = protocolo.recibir_nombre();
	std::vector<std::string> lista_hash;
	for (int i = CERO; i < cantidad_hash; ++i){
		std::string aux;
		aux = protocolo.recibir_nombre();
		lista_hash.push_back(aux);
	}
	Sincronizar sincronizar(m);
	if (!(sistema.tag_valido(nom_tag,lista_hash))){
		protocolo.enviar_accion(CERO);
	}else{
		sistema.do_tag(nom_tag,lista_hash);
		protocolo.enviar_accion(VALID);
	}
	proceso_terminado=true;
}





