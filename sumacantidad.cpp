#include "sumacantidad.h"

SumaCantidad::SumaCantidad(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor)
    :Modelo(_colorRef,_nombre,_lado),valorSuma(_valor)
{

}

//Metodos getters y setters
int SumaCantidad::getValorSuma(){
    return this->valorSuma;
}

void SumaCantidad::setValorSuma(int _valor){
    this->valorSuma = _valor;
}

void SumaCantidad::sumarCantidad(){

}
