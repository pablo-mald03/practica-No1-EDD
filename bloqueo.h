#ifndef BLOQUEO_H
#define BLOQUEO_H

#include"modelo.h"

class Bloqueo:public Modelo
{
public:
    Bloqueo(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~Bloqueo();

    //Metodo de bloqueo
    void bloquearJugador();
    std::string getPathImagen() const override;
};

#endif // BLOQUEO_H
