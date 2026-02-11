#include "reversa.h"

Reversa::Reversa(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::Reverse)
{

}

//Metodo que sirve para poder voltear el modo flip
void Reversa::voltearMazos(){

}

Reversa::~Reversa(){

}
