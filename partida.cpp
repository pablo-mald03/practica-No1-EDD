#include "partida.h"
#include"mainwindow.h"

Partida::Partida(int _cantidadJugadores,DatosConfiguracion* &config)
    :cantidadJugadores(_cantidadJugadores),listaJugadores(), configuracion(config)
{
    generarJugadores();

    Jugador* j1 = nullptr;

    try{
        for (int var = 0; var <= this->listaJugadores.getLongitud(); ++var) {

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

    delete config;
    config = nullptr;
}
void Partida::generarJugadores(){
    for (int i = 0; i < this->cantidadJugadores; ++i) {
        this->listaJugadores.insertar(new Jugador("Jugador " + std::to_string(i + 1), i));
    }
}

Partida::~Partida(){

}
