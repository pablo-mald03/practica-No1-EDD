#include "bloqueo.h"

Bloqueo::Bloqueo(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CartaBloqueo)
{

}

//Metodo de bloqueo
void Bloqueo::bloquearJugador(){

}

Bloqueo::~Bloqueo(){

}
