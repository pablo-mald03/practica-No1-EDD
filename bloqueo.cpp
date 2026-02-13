#include "bloqueo.h"

Bloqueo::Bloqueo(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CartaBloqueo)
{

}

//Metodo de bloqueo
void Bloqueo::bloquearJugador(){

}

//Metodo que retorna el valor de imagen de la carta
std::string Bloqueo::getPathImagen() const{

    if(Modelo::getColor().getColorCarta() == TipoColor::AMARILLO){
        return ":/assets/mediaGame/CartaYBlock.png";
    }
    else if(Modelo::getColor().getColorCarta() == TipoColor::AZUL){
        return ":/assets/mediaGame/CartaABlock.png";
    }
    else if(Modelo::getColor().getColorCarta() == TipoColor::ROJO){
        return ":/assets/mediaGame/CartaRBlock.png";
    }
    else if(Modelo::getColor().getColorCarta() == TipoColor::VERDE){
        return ":/assets/mediaGame/CartaVBlock.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}

Bloqueo::~Bloqueo(){

}
