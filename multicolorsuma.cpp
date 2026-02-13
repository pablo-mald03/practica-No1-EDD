#include "multicolorsuma.h"

MultiColorSuma::MultiColorSuma(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::SumaMulticolor),valorSuma(_valor)  {}

int MultiColorSuma::getValorSuma(){
    return this->valorSuma;
}

void MultiColorSuma::setValorSuma(int _valor){
    this->valorSuma = _valor;
}

//Metodo que retorna el valor de imagen de la carta
std::string MultiColorSuma::getPathImagen() const{

    if(Modelo::getLado() == "claro" && this->valorSuma == 2){
        return ":/assets/mediaGame/CartaMas2.png";
    }
    else if(Modelo::getLado() == "claro" && this->valorSuma == 4){
        return ":/assets/mediaGame/CartaMas4.png";
    }
    else if(Modelo::getLado() == "oscuro" && this->valorSuma == 6){
        return ":/assets/mediaGame/CartaMas6.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}

MultiColorSuma::~MultiColorSuma(){

}
