#ifndef CAMBIODIRECCION_H
#define CAMBIODIRECCION_H

#include"modelo.h"

class CambioDireccion:public Modelo
{
public:
    CambioDireccion(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~CambioDireccion();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;

    //Metodo donde se requiera mover a la lista de jugadores
    void lanzarCarta(ListaCircular<Jugador*> & jugador) override;

    //Caso donde la carta debe interactuar con la partida
    void lanzarCarta(Partida & partidaActual) override;

    //Caso donde la carta debe interactuar con la partida y un jugador x
    void lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) override;
};

#endif // CAMBIODIRECCION_H
