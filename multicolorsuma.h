#ifndef MULTICOLORSUMA_H
#define MULTICOLORSUMA_H

#include"modelo.h"
class MultiColorSuma: public Modelo
{

private:
    int valorSuma;

public:
    MultiColorSuma(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor);
    ~MultiColorSuma();

    //Metodos
    int getValorSuma();
    void setValorSuma(int _valor);


};

#endif // MULTICOLORSUMA_H
