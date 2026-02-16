#ifndef MODELO_H
#define MODELO_H

#include<string>

//includes de clases
#include"colorcarta.h"
//Forward declaration
class Partida;
class Jugador;
template<typename T>
class ListaEnlazada;
template<typename T>
class ListaCircular;

//Enums utilizados para poder evitar el casteo dinamico
enum class TipoCarta {
    Predeterminado,
    CARTANUMERICA,
    CARTABLOQUEO,
    ETERNA,
    SUMAMULTICOLOR,
    SUMARCANTIDAD,
    CAMBIARDIRECCION,
    COLORCOMODIN,
    CARTAESPIA,
    CARTAECLIPSE,
    REVERSE,
    SALTOTOTAL

};

class Modelo
{

protected:
    std::string nombre;
    ColorCarta color;
    std::string lado;
    TipoCarta tipo;

    //Atributo para saber a que jerarquia pertenece
    int jerarquia;

public:
    Modelo(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,
    TipoCarta _tipo, int _jerarquia);
   // Modelo();
    virtual ~Modelo();

    //Metodos getter y setter
    void setColor(const ColorCarta &_color);
    void setNombre(const std::string &_nombre);
    void setLado(const std::string &_lado);
    std::string getNombre()const;
    ColorCarta getColor()const;
    std::string getLado()const;
    TipoCarta getTipo()const;

    int getJerarquia()const;

    //Metodo para obtener el reverso
    std::string getReversoModelo()const;

    //Metodos virtuales
    virtual std::string getPathImagen() const = 0;
    //Metodos sobrecargados

    //Metodo base cuando una carta tiene que interactuar con un jugador x
    virtual void lanzarCarta(ListaCircular<Jugador*> & jugador) = 0;
    //Caso donde la carta debe interactuar con la partida
    virtual void lanzarCarta(Partida & partidaActual) = 0;
    //Caso donde la carta debe interactuar con la partida y un jugador x
    virtual void lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) = 0;

};

#endif // MODELO_H
