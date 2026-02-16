#ifndef NUMERICA_H
#define NUMERICA_H

#include "modelo.h"

class Numerica:public Modelo
{

private:
    int valor;

    std::string getDirectoriosRosa() const;
    std::string getDirectoriosVioleta() const;
    std::string getDirectoriosTurquesa() const;
    std::string getDirectoriosNaranja() const;
    std::string getDirectoriosRojo() const;
    std::string getDirectoriosAzul() const;
    std::string getDirectoriosAmarillo() const;
    std::string getDirectoriosVerde() const;



public:
    Numerica(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor,int _jerarquia);

    int getValor() const;

    ~Numerica();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;

    //Metodo donde se requiera mover a la lista de jugadores
    void lanzarCarta(ListaCircular<Jugador*> & jugador) override;

    //Caso donde la carta debe interactuar con la partida
    void lanzarCarta(Partida & partidaActual) override;

    //Caso donde la carta debe interactuar con la partida y un jugador x
    void lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) override;

};

#endif // NUMERICA_H
