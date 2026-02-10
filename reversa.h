#ifndef REVERSA_H
#define REVERSA_H

#include"modelo.h"

class Reversa:public Modelo
{
public:
    Reversa(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~Reversa();

    //Metodo que sirve para poder voltear el modo flip
    void voltearMazos();
};

#endif // REVERSA_H
