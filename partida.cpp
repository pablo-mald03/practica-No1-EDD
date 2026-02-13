#include "partida.h"
#include"mainwindow.h"

Partida::Partida(int _cantidadJugadores,DatosConfiguracion* &config)
    :cantidadJugadores(_cantidadJugadores),listaJugadores(), configuracion(config)
{
    generarJugadores();

    Jugador* j1 = nullptr;

    delete config;
    config = nullptr;
}
void Partida::generarJugadores(){
    for (int i = 0; i < this->cantidadJugadores; ++i) {
        this->listaJugadores.insertar(new Jugador("Jugador " + std::to_string(i + 1), i));
    }
}

Jugador* & Partida::getJugadorActual(){
    return this->listaJugadores.getActual();
}


Partida::~Partida(){

}
