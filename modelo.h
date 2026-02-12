#ifndef MODELO_H
#define MODELO_H

#include<string>

//includes de clases
#include"colorcarta.h"

//Enums utilizados para poder evitar el casteo dinamico
enum class TipoCarta {
    CartaNumerica,
    CartaBloqueo,
    Eterna,
    SumaMulticolor,
    SumarCantidad,
    CambiarDireccion,
    ColorComodin,
    CartaEspia,
    CartaEclipse,
    Reverse

};

class Modelo
{

protected:
    std::string nombre;
    ColorCarta color;
    std::string lado;
    TipoCarta tipo;

public:
    Modelo(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,
    TipoCarta _tipo);
    virtual ~Modelo();

    //Metodos getter y setter
    void setColor(const ColorCarta &_color);
    void setNombre(const std::string &_nombre);
    void setLado(const std::string &_lado);
    std::string getNombre()const;
    ColorCarta getColor()const;
    std::string getLado()const;
    TipoCarta getTipo()const;

    //Metodos sobrecargados


};

#endif // MODELO_H
