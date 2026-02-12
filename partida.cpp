#include "partida.h"
#include"mainwindow.h"

Partida::Partida(DatosConfiguracion* &config)
    :listaJugadores(), configuracion(config)
{

    this->listaJugadores.insertar(new Jugador("Pedro1", 1));
    this->listaJugadores.insertar(new Jugador("Pedro2", 2));

    Jugador* j1 = nullptr;

    try{
        for (int var = 0; var < 5; ++var) {

            j1 = this->listaJugadores.getActual();

            qDebug() << "Nombre del jugador primero: "<<j1->getNombre();
            qDebug() << "Codigo del jugador primero: "<<j1->getCodigo();

            j1 = nullptr;
            qDebug() << "Avanzando en la lista...\n";
            this->listaJugadores.avanzar();
        }

    }catch(const std::runtime_error & ex){
        qDebug() << "La lista esta vacia...\n";
    }
}

Partida::~Partida(){

}
