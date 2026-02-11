#include "comodincolor.h"

ComodinColor::ComodinColor(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::ColorComodin)
{

}

//Metodo de cambio
void ComodinColor::cambiarDireccion(){

}


ComodinColor::~ComodinColor(){

}
