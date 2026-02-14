#ifndef SUMACANTIDAD_H
#define SUMACANTIDAD_H

#include"modelo.h"


class SumaCantidad: public Modelo
{

private:
    int valorSuma;
public:
    SumaCantidad(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor);

    ~SumaCantidad();

    //Metodos getters y setters
    int getValorSuma();
    void setValorSuma(int _valor);
    void sumarCantidad();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;

};

#endif // SUMACANTIDAD_H
