#include "coloreterno.h"

ColorEterno::ColorEterno(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::Eterna) {}


void ColorEterno::saltoTotal(){


}

std::string ColorEterno::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        return ":/assets/mediaGame/CartaEcplipse.png";
    }
    else if(Modelo::getLado() == "oscuro"){
        return ":/assets/mediaGame/CartaEcplipseNegra.png";
    }

    //PENDIENTE
    return ":/assets/mediaGame/CartaVBlock.png";
}

ColorEterno::~ColorEterno(){

}
