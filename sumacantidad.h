#ifndef SUMACANTIDAD_H
#define SUMACANTIDAD_H

#include"modelo.h"


class SumaCantidad: public Modelo
{

private:
    int valorSuma;
public:
    SumaCantidad(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia, int _valor);

    ~SumaCantidad();

    //Metodos getters y setters
    int getValorSuma();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;

    //Metodo donde se requiera mover a la lista de jugadores
    void lanzarCarta(ListaCircular<Jugador*> & jugador) override;

    //Caso donde la carta debe interactuar con la partida
    void lanzarCarta(Partida & partidaActual) override;

    //Caso donde la carta debe interactuar con la partida y un jugador x
    void lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) override;

};

#endif // SUMACANTIDAD_H
