#ifndef ESPIA_H
#define ESPIA_H

#include"modelo.h"

class Espia:public Modelo
{
public:
    Espia(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia);
    ~Espia(); 

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;

    //Metodo donde se requiera mover a la lista de jugadores
    void lanzarCarta(ListaCircular<Jugador*> & jugador) override;

    //Caso donde la carta debe interactuar con la partida
    void lanzarCarta(Partida & partidaActual) override;

    //Caso donde la carta debe interactuar con la partida y un jugador x
    void lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) override;
};

#endif // ESPIA_H
