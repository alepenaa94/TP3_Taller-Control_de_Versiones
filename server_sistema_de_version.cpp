#include <vector>
#include <string>
#include "sistema_de_version.h"
#include <iostream>


Sistema_de_version::Sistema_de_version(std::string& name_f):name_f(name_f){
    indice = new Indice(name_f); //genero el indice en memoria
}

Sistema_de_version::~Sistema_de_version(){
	delete(indice);
}

bool Sistema_de_version::pull_valido(std::string& tag){
    return indice->contiene_tag(tag);
}

bool Sistema_de_version::tag_valido(std::string& tag,
									std::vector<std::string>& lista_hash){
    for (unsigned int i = 0; i < lista_hash.size(); ++i){
    	if(!(indice->contiene_hash(lista_hash[i]))){
    		return false;
    	}
    }
    return !(indice->contiene_tag(tag));
}

bool Sistema_de_version::push_valido(std::string& hash){
    return !(indice->contiene_hash(hash));
}

void Sistema_de_version::actualizar_indice(){
	indice->gen_indice_nuevo();
}

std::vector<std::string>& Sistema_de_version::do_pull(std::string& tag){
        return indice->get_value_tag(tag);
}

void Sistema_de_version::do_tag(std::string& tag,
 								std::vector<std::string> lista_hash){
    indice->set_tag(tag,lista_hash);    
}

void Sistema_de_version::do_push(std::string& nom_archivo, std::string& hash){
    	indice->set_push(hash,nom_archivo);
}

std::string& Sistema_de_version::get_hash(std::string& hash){
    return indice->get_value_hash(hash);
}
















