#include "eclipse.h"

Eclipse::Eclipse(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CartaEclipse)
{

}


//Metodo para esconder mazo
void Eclipse::esconderMazo(){

}

Eclipse::~Eclipse(){

}
