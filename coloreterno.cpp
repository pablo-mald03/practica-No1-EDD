#include "coloreterno.h"

ColorEterno::ColorEterno(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::Eterna) {}


void ColorEterno::saltoTotal(){


}

//Metodo que retorna el valor de imagen de la carta
std::string ColorEterno::getPathImagen() const{

    if(Modelo::getLado() == "oscuro"){
        return ":/assets/mediaGame/CartaColorEterno.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}

ColorEterno::~ColorEterno(){

}
