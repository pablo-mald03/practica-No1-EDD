#include "espia.h"

Espia::Espia(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado, TipoCarta::CartaEspia)
{

}

//Metodo de revelacion
void Espia::revelarMazo(){

}


//Metodo que retorna el valor de imagen de la carta
std::string Espia::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        return ":/assets/mediaGame/CartaEspia.png";
    }else if(Modelo::getLado() == "oscuro"){
        return ":/assets/mediaGame/CartaEspiaNegra.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}

Espia::~Espia(){

}

