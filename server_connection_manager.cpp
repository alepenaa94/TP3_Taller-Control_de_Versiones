#include "connection_manager.h"
#include "Protocolo.h"
#include <vector>


Connection_manager::Connection_manager(Socket* srv, Sistema_de_version& sist):
								srv(srv), sist(sist), aceptar_cliente(true){}

void check_pedidos_listos(std::vector<Pedido_clt*>& lista_procesos){
	for (unsigned int i = 0; i < lista_procesos.size(); ++i){
			if(lista_procesos[i]->is_finish()){
				lista_procesos[i]->join();
				delete(lista_procesos[i]->get_conexion());
       			delete(lista_procesos[i]);
       			lista_procesos.erase(lista_procesos.begin()+i);
			}
		}
}

void Connection_manager::run(){
	std::mutex m;
	while(aceptar_cliente){ 
		Socket* clt = srv->server_aceptar_clt();
		if(clt==nullptr){
			if(!aceptar_cliente){
				break;	
			}
			std::cout<<"error al conectar el cliente..."<<'\n';
		}
		Protocolo protocolo(clt);
		lista_procesos.push_back(new Pedido_clt(clt,sist,m,protocolo));
		(lista_procesos.back())->start();
		
		check_pedidos_listos(lista_procesos);
	}
}



void Connection_manager::stop_acept(){
	aceptar_cliente=false;
}

Connection_manager::~Connection_manager(){
	check_pedidos_listos(lista_procesos);	
}

