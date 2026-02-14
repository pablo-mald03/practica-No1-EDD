#ifndef COMODINCOLOR_H
#define COMODINCOLOR_H

#include"modelo.h"

class ComodinColor:public Modelo
{
public:
    ComodinColor(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~ComodinColor();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;

    //Metodo donde se requiera mover a la lista de jugadores
    void lanzarCarta(ListaCircular<Jugador*> & jugador) override;

    //Caso donde la carta debe interactuar con la partida
    void lanzarCarta(Partida & partidaActual) override;

    //Caso donde la carta debe interactuar con la partida y un jugador x
    void lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) override;

};

#endif // COMODINCOLOR_H
