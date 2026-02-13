#ifndef COMODINCOLOR_H
#define COMODINCOLOR_H

#include"modelo.h"

class ComodinColor:public Modelo
{
public:
    ComodinColor(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~ComodinColor();

    //Metodo de cambio
    void cambiarDireccion();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;

};

#endif // COMODINCOLOR_H
