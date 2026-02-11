#include "cambiodireccion.h"

CambioDireccion::CambioDireccion(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CambiarDireccion)
{

}

//Metodo de cambio
void CambioDireccion::cambiarDireccion(){

}

CambioDireccion::~CambioDireccion(){

}
