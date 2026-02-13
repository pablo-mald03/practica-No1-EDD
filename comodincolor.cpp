#include "comodincolor.h"

ComodinColor::ComodinColor(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::ColorComodin)
{

}

//Metodo de cambio
void ComodinColor::cambiarDireccion(){

}

//Metodo que retorna el valor de imagen de la carta
std::string ComodinColor::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        return ":/assets/mediaGame/CartaSeleccion.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}


ComodinColor::~ComodinColor(){

}
