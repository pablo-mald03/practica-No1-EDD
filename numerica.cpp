#include "numerica.h"

Numerica::Numerica(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CartaNumerica),valor(_valor)
{}

//Metodos getters y setters
int Numerica::getValor()const {
    return this->valor;
}

void Numerica::setValor(int _valor){
     this->valor = _valor;
}

Numerica::~Numerica(){

}
