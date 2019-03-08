#ifndef PEDIDO_CLT_H
#define PEDIDO_CLT_H
#include "socket.h"
#include "sistema_de_version.h"
#include "Thread.h"
#include <string>
#include <mutex>
#include "Protocolo.h"

class Pedido_clt : public Thread{
    private:
        Socket* conexion;
        Sistema_de_version& sistema;
        bool proceso_terminado;
        std::mutex &m;
        void proceso_push();
        void proceso_tag();
        void proceso_pull();
        Protocolo& protocolo;
        //fin priv
    public:
        /*Constructor del proceso del cliente. Recibe la conexion del server
        con el cliente, el sistema, el protocolo y mutex.*/
        Pedido_clt(Socket* conexion,Sistema_de_version& sistema,std::mutex& m,
                        Protocolo& protocolo);
        /*Constructor por movimiento*/
        Pedido_clt(Pedido_clt&& other);
        /*Constructor por copia no permitido*/
        Pedido_clt& operator=(const Pedido_clt& other)=delete;
        /*Constructor por copia no permitido*/
        Pedido_clt(const Pedido_clt& other)=delete;
         /*Devuelve la conexion con la que se creo el pedido del cliente.*/
        Socket* get_conexion();
        /*Devuelve true si se termino el clt_process*/
		bool is_finish();
        /*Metodo run de la clase Thread. Analiza y procesa lo pedido por el 
        cliente, mediante la comunicacion del socket establecido.*/
        virtual void run() override;
};

#endif


