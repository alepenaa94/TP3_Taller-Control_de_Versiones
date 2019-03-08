#include <iostream>
#include "socket.h"
#include "sistema_de_version.h"
#include "Thread.h"
#include "connection_manager.h"
#include <string>
#include "Protocolo.h"

int main(int argc, char *argv[]){	
	if(argc!=3){
		//parametros incorrectos
		return 1;
	}
	std::string puerto(argv[1]);
	std::string name_ind(argv[2]);
	Socket* srv = new Socket(puerto);
	Sistema_de_version sist(name_ind);
	Connection_manager* connection_man = new Connection_manager(srv,sist);
	connection_man->start();
	bool server_on=true;
	char letter;
	while(server_on){
		std::cin>>letter;
		if(letter=='q'){
			server_on=false;
		}
	}
	connection_man->stop_acept();
	delete(srv);
	connection_man->join();
	delete(connection_man);
	sist.actualizar_indice();
	return 0;
}



