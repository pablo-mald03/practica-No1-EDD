#ifndef ECLIPSE_H
#define ECLIPSE_H

#include"modelo.h"

class Eclipse:public Modelo
{
public:
    Eclipse(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~Eclipse();

    //Metodo para esconder mazo
    void esconderMazo();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;
};

#endif // ECLIPSE_H
