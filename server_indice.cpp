#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "indice.h"
#include <iostream>
#include "exception_tag.h"
#include "exception_open_file.h"
#include "exception_hash.h"
#include <map>
#define ESPACIO 32
#define PUNTO_COMA 59
#define SALTO_LINEA 10


Indice::Indice(Indice&& other){
    nomb_file=other.nomb_file;
}

Indice::Indice(std::string& nomb_file): nomb_file(nomb_file){
    myfile.open(nomb_file, std::ifstream::in);
    if ( !myfile.is_open() ){
        throw Open_file_Error("Error: archivo indice no encontrado.");
    }
    std::string texto;
    char anterior= ESPACIO; //por default
    std::vector<std::string> parametros2;
    while (true){
        char buff;
        myfile.get(buff);
        if ( myfile.eof() ){
            break;
        }
        if (buff==SALTO_LINEA){
            continue;
        }
        if (buff==PUNTO_COMA){
            if (anterior!=ESPACIO){
                parametros2.push_back(texto);
            }
            parametros.push_back(parametros2);
            parametros2.clear();
            texto.clear();
            anterior=ESPACIO;
            continue;
        }
        if (buff==ESPACIO && anterior==ESPACIO){
            anterior = ESPACIO;
            continue;
        }
        if (buff==ESPACIO && anterior!=ESPACIO){
            //nuevo item en el vector...
            parametros2.push_back(texto);
            texto.clear(); //asi cargo un nuevo texto
            anterior = ESPACIO;    
            continue;
        }
        texto.push_back(buff);
        anterior = buff;
    }
    //Ahora cargo los mapas..
    for (unsigned int i = 0; i < parametros.size(); i++){
        if (parametros[i][0] == "f"){
            this->gen_map_hash(parametros[i]);
        }else{
            this->gen_map_tag(parametros[i]);
        }
    }
    myfile.close();
}

void Indice::gen_map_hash(std::vector<std::string>& vect){
    std::string nombre = vect[1];
    for (unsigned int i = 2; i < vect.size(); i++){
        map_hash[vect[i]]=nombre;
    }
}

void Indice::gen_map_tag(std::vector<std::string>& vect){
    std::vector<std::string> aux(vect.begin() + 2, vect.end());
    map_tag[vect[1]]= aux;
}

bool Indice::contiene_hash(std::string& txt){
    return (map_hash.count(txt)>0);
}

bool Indice::contiene_tag(std::string& txt){
    return (map_tag.count(txt)>0);
}


void Indice::set_tag(std::string& tag,std::vector<std::string>& lista_hash){
    if (this->contiene_tag(tag)){
        throw Tag_Error("Error al setear nuevo tag(tag existente).");
    }
    std::sort(lista_hash.begin(),lista_hash.end());
    map_tag[tag]=lista_hash;
}





void Indice::set_push(std::string& hash,std::string& archivo){
    if (this->contiene_hash(hash)){
        throw Hash_Error("Error al setear nuevo hash(hash existente).");
    }
    map_hash[hash]=archivo;
}






void Indice::ordenar(){
	/*La idea es cargar en el mapa como clave el nombre del archivo y como 
	valor los hashes asosiados... Recorro el primer mapa, si existe la clave 
	agrego el valor a continuacion de la lista.. sino genero una lista 
	con un unico elemento. */
	std::map<std::string,std::vector<std::string>> map_aux;
    std::map<std::string,std::string>::iterator it;
	for(it = map_hash.begin(); it != map_hash.end(); ++it){
		std::map<std::string,std::vector<std::string>>::iterator it2;
		it2=map_aux.find(it->second);
		if(it2==map_aux.end()){
			//significa que no existe la clave archivo..
            // entonce tengo que crearla con lista de un elemento
			std::vector<std::string> v;
			v.push_back(it->first);
			map_aux[it->second]=v;
		}else{
			/*existe la clave entonces simpplemente agrego al final.. y como
			el mapa al cargarlo por default ordena en orden alfabetico
			al agregar los hashes, ya estan ordenados.. asique luego solo tengo
			que imprimir con un iterator, el primer elemento y luego sus hashes
			y asi...*/
			(it2->second).push_back(it->first);
		}
	}
	map_f = map_aux;
}



std::vector<std::string>& Indice::get_value_tag(std::string& tag){
    std::map<std::string,std::vector<std::string>>::iterator it;
    it = map_tag.find(tag);
    if (it == map_tag.end()){
        throw Tag_Error("Error: tag no encontrado.");
    }
    return it->second;
}

std::string& Indice::get_value_hash(std::string& hash){
    std::map<std::string,std::string>::iterator it;
    it = map_hash.find(hash);
    if (it == map_hash.end()){
        throw Hash_Error("Error: hash no encontrado.");
    }
    return it->second;
}


void Indice::gen_indice_nuevo(){
	myfile2.open(nomb_file, std::ofstream::out);
	this->ordenar();
    std::map<std::string,std::vector<std::string>>::iterator it; 
	for(it = map_f.begin(); it != map_f.end(); ++it){
		myfile2<<"f ";
		myfile2<<(it->first);
		for (unsigned int i = 0; i < (it->second).size(); i++){
			myfile2<<" ";
			myfile2<<(it->second)[i];	
		}
		myfile2<<" ;";
		myfile2<<'\n';
	}
    std::map<std::string,std::vector<std::string>>::iterator it2;
	for(it2 = map_tag.begin(); it2 != map_tag.end(); ++it2){
		myfile2<<"t ";
		myfile2<<(it2->first);	
		for (unsigned int i = 0; i < (it2->second).size(); i++){
			myfile2<<" ";
			myfile2<<(it2->second)[i];	
		}
		myfile2<<" ;";
		myfile2<<'\n';
	}
    myfile2.close();
}




Indice::~Indice(){}






