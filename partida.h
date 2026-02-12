#ifndef PARTIDA_H
#define PARTIDA_H

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

public:
    Partida(DatosConfiguracion* &config);
    ~Partida();
};

#endif // PARTIDA_H
