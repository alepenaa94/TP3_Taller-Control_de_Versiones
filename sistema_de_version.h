#ifndef SISTEMA_DE_VERSION_H
#define SISTEMA_DE_VERSION_H
#include <vector>
#include <string>
#include "indice.h"

class Sistema_de_version{
    private:
        Indice* indice;
        std::string& name_f;
        //fin vars privadas
    public:
        /*Constructor por copia no permitido*/
        Sistema_de_version(const Sistema_de_version& other)=delete;
        /*Operador = no permitido*/
    	Sistema_de_version& operator=(const Sistema_de_version& other)=delete;
    	/*Constructor: intenta crear la conexion segun sea si es para cliente
        o servidor */
        explicit Sistema_de_version(std::string& iname_f);
        /*Constructor por movimiento*/
        Sistema_de_version(Sistema_de_version&& other);
        /*Destructor: se elimina de memoria los paquetes*/
        virtual ~Sistema_de_version();

        /*La funcion pull_valido chequea que el tag exista en el sistema*/
        bool pull_valido(std::string& tag);

        /*La funcion devuelve un vector de strings en donde cada
        uno de los strings son los hashes correspondientes al tag pasado
        por parametro. Si no existe el tag, lanza excepcion.*/
        std::vector<std::string>& do_pull(std::string& tag);

        /*La funcion tag_valido chequea si el tag es valido para hacer.*/
        bool tag_valido(std::string& tag,std::vector<std::string>& lista_hash);

        /*Realiza un tag en el sistema, para los hashes pasados en la lista.
        En caso de no poder, lanza una excepcion.*/
        void do_tag(std::string& tag, std::vector<std::string> lista_hash);

        /*La funcion push_valido chequea que el hash sea valido para 
        realizar un push en el sistema.*/
        bool push_valido(std::string& hash);

        /*Realiza un push en el sistema, del archivo con su hash pasado
        por parametros. En el caso de que no sea valido el hash, lanza
        una excepcion.*/
        void do_push(std::string& nom_archivo, std::string& hash); 

        //al hash asociado devuelve el nombre del archivo..
        std::string& get_hash(std::string& hash);

        void actualizar_indice();
};
#endif
