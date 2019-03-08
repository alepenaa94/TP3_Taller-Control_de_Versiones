#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H
#include "socket.h"
#include <string>
#include "Thread.h"
#include <vector>
#include "pedido_clt.h"

class Connection_manager : public Thread {
    private:
        Socket* srv;
        std::vector<Pedido_clt*> lista_procesos;
        Sistema_de_version& sist;
        bool aceptar_cliente;
    public:
        /*Constructor: recibe un puntero del servidor y un sistema.*/
        Connection_manager(Socket* srv, Sistema_de_version& sist); 
        /*Constructor por movimiento*/
        Connection_manager(Connection_manager&& other);
        /*Destructor*/
        ~Connection_manager();
        /*Constructor por copia no permitido*/
        Connection_manager& operator=(const Connection_manager& other)=delete;
        /*Constructor por copia no permitido*/
        Connection_manager(const Connection_manager& other)=delete;
        /*Frena el estado de aceptacion del servidor, se debe cerrar luego el 
        server.*/
        void stop_acept();
        virtual void run() override;// a implementar el override del Thread..
};

#endif


