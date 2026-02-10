#ifndef COLORETERNO_H
#define COLORETERNO_H

#include"modelo.h"

class ColorEterno: public Modelo
{
public:
    ColorEterno(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~ColorEterno();

    void saltoTotal();
};

#endif // COLORETERNO_H
