#ifndef MODELO_H
#define MODELO_H

#include<string>

//includes de clases
#include"colorcarta.h"

class Modelo
{

protected:
    std::string nombre;
    ColorCarta color;
    std::string lado;

public:
    Modelo(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~Modelo();

    //Metodos getter y setter
    void setColor(const ColorCarta &_color);
    void setNombre(std::string _nombre);
    void setLado(std::string _lado);
    std::string getNombre()const;
    ColorCarta getColor()const;
    std::string getLado()const;

};

#endif // MODELO_H
