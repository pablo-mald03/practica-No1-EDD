#ifndef PARTIDA_H
#define PARTIDA_H

//Includes de C++
#include<string>

//Declaracion del struct usado
struct DatosConfiguracion;

//Includes de las clases propias
#include"listacircular.h"
#include"jugador.h"
#include"configuracionpartida.h"

class Partida
{
private:
    ListaCircular<Jugador*> listaJugadores;
    ConfiguracionPartida configuracion;
    int cantidadJugadores;
    std::string direccion;

    //Metodos propios de la clase para hacer funcionar la partida
    void generarJugadores();
    int generarIndiceRandom(int limiteSuperior);
    void correrIndices();


    //Metodo de una sola utilidad
    void generarDireccionInicial();

public:
    Partida(int _cantidadJugadores,DatosConfiguracion* &config);
    ~Partida();


    //Apartado de comunicacion de backend con las acciones que deba ejecutar frontend
    Jugador* & getJugadorActual();

    //Metodo que permite obtener la direccion
    std::string getDireccion();
};

#endif // PARTIDA_H
