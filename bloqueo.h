#ifndef BLOQUEO_H
#define BLOQUEO_H

#include"modelo.h"
#include"listacircular.h"
#include"jugador.h"
#include"partida.h"

class Bloqueo:public Modelo
{
public:
    Bloqueo(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia);
    ~Bloqueo();

    //Metodo para obtener el directorio de la imagen de la carta
    std::string getPathImagen() const override;

    //Metodo donde se requiera mover a la lista de jugadores
    void lanzarCarta(ListaCircular<Jugador*> & jugador) override;

    //Caso donde la carta debe interactuar con la partida
    void lanzarCarta(Partida & partidaActual) override;

    //Caso donde la carta debe interactuar con la partida y un jugador x
    void lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) override;

};

#endif // BLOQUEO_H
