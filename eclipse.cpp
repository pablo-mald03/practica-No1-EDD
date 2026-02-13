#include "eclipse.h"

Eclipse::Eclipse(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CartaEclipse)
{

}


//Metodo para esconder mazo
void Eclipse::esconderMazo(){

}

//Metodo que retorna el valor de imagen de la carta
std::string Eclipse::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        return ":/assets/mediaGame/CartaEcplipse.png";
    }else if(Modelo::getLado() == "oscuro"){
        return ":/assets/mediaGame/CartaEcplipseNegra.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}

Eclipse::~Eclipse(){

}
