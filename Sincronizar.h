#ifndef SINCRONIZAR_H
#define SINCRONIZAR_H
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

/*Clase para realizar la sincronizacion de metodos, para que no se 
produzca race condition*/

class Sincronizar {
    private:
        std::mutex &m;
        /*Constructor por copia no permitido*/
        Sincronizar(const Sincronizar&) = delete;
        /*Operador = no permitido*/
        Sincronizar& operator=(const Sincronizar&) = delete;
        /*Constructor por movimiento no permitido*/
        Sincronizar(Sincronizar&&) = delete;
        /*Operador = no permitido*/
        Sincronizar& operator=(Sincronizar&&) = delete;
    public:
        /*Constructor que crea un mutex en memoria*/
        explicit Sincronizar(std::mutex &m);
        /*Destructor que destruye en memoria el mutex almacenado*/
        ~Sincronizar();
};
#endif

