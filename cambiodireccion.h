#ifndef CAMBIODIRECCION_H
#define CAMBIODIRECCION_H

#include"modelo.h"

class CambioDireccion:public Modelo
{
public:
    CambioDireccion(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~CambioDireccion();

    //Metodo de cambio
    void cambiarDireccion();
    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;
};

#endif // CAMBIODIRECCION_H
