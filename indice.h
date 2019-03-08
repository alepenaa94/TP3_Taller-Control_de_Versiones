#ifndef INDICE_H
#define INDICE_H
#include <vector>
#include <fstream>
#include <string>
#include <map>

class Indice{
    private:
        std::map<std::string,std::vector<std::string>> map_tag; // tag:listahash
        std::map<std::string,std::string> map_hash; // hash:nom_arch
        std::map<std::string,std::vector<std::string>> map_f; // arch:listahash
        std::ifstream myfile;
        std::ofstream myfile2;
        std::string nomb_file;
        std::vector< std::vector<std::string> > parametros;
        void gen_map_hash(std::vector<std::string>& vect);
        void gen_map_tag(std::vector<std::string>& vect);
        //fin vars privadas
    public:
        /*Constructor por copia no permitido*/
        Indice(const Indice& other)=delete;
        /*Operador = no permitido*/
    	Indice& operator=(const Indice& other)=delete;
    	/*Constructor: intenta crear la conexion segun sea si es para cliente
        o servidor */
        explicit Indice(std::string& nomb_file);
        /*Constructor por movimiento*/
        Indice(Indice&& other);
        /*Destructor: se elimina de memoria los paquetes*/
        ~Indice();
        /*Devuelve bool segun si contiene o no el hash*/
        bool contiene_hash(std::string& txt);
        /*Devuelve bool segun si contiene o no el tag*/
        bool contiene_tag(std::string& txt);
        /*Devuelve lo asociado al tag pasado por parametro*/
        std::vector<std::string>& get_value_tag(std::string& tag);
        /*Setea el tag.*/
        void set_tag(std::string& tag,std::vector<std::string>& lista_hash);
        /*Ordena el indice*/
        void ordenar();
        /*Genera el indice nuevo, con el mismo nombre.*/
        void gen_indice_nuevo();
        /*Setea el map_hash, con el contenido pasado.*/
        void set_push(std::string& hash,std::string& archivo);
        /*Devuelve lo asociado al hash pasado por parametro*/
        std::string& get_value_hash(std::string& hash);
};
    

#endif
