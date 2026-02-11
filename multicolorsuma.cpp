#include "multicolorsuma.h"

MultiColorSuma::MultiColorSuma(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::SumaMulticolor),valorSuma(_valor)  {}

int MultiColorSuma::getValorSuma(){
    return this->valorSuma;
}

void MultiColorSuma::setValorSuma(int _valor){
    this->valorSuma = _valor;
}

MultiColorSuma::~MultiColorSuma(){

}
