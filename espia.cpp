#include "espia.h"

Espia::Espia(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado, TipoCarta::CartaEspia)
{

}

//Metodo de revelacion
void Espia::revelarMazo(){

}

Espia::~Espia(){

}

