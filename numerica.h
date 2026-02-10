#ifndef NUMERICA_H
#define NUMERICA_H

#include "modelo.h"

class Numerica:public Modelo
{

private:
    int valor;

public:
    Numerica(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor);

    int getValor() const;
    void setValor(int _valor);

    ~Numerica();
};

#endif // NUMERICA_H
