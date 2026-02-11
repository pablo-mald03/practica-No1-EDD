#include "configuracionpartida.h"

ConfiguracionPartida::ConfiguracionPartida(bool _stacking, bool _reto4, bool _modoRobo, bool _gritoUno, bool _ganarNegra, bool _esFlip)
    :stacking(_stacking), retoMas4(_reto4),modoRobo(_modoRobo), gritoUno(_gritoUno), ganarNegra(_ganarNegra), flip(_esFlip)
{

}

//Metodos getter para saber los estados de configuracion
bool ConfiguracionPartida::esStacking()const{
    return this->stacking;
}

bool ConfiguracionPartida::esRetoMas4()const{
    return this->retoMas4;
}

bool ConfiguracionPartida::esModoRobo()const{
    return this->modoRobo;
}

bool ConfiguracionPartida::esGritoUno()const{
    return this->gritoUno;
}

bool ConfiguracionPartida::esGanarNegra()const{
    return this->ganarNegra;
}

bool ConfiguracionPartida::esFlip()const{
    return this->flip;
}

ConfiguracionPartida::~ConfiguracionPartida(){

}
