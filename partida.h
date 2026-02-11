#ifndef PARTIDA_H
#define PARTIDA_H

//Declaracion del struct usado
struct DatosConfiguracion;

//Includes de las clases propias
#include"listaenlazada.h"
#include"modelo.h"
#include"jugador.h"
#include"configuracionpartida.h"

class Partida
{
private:
    ListaEnlazada<Jugador*> *listaJugadores;
    ConfiguracionPartida *configuracion;

public:
    Partida(const DatosConfiguracion* &config);
    ~Partida();
};

#endif // PARTIDA_H
