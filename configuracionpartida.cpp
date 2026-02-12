#include "configuracionpartida.h"
#include"mainwindow.h"

ConfiguracionPartida::ConfiguracionPartida(DatosConfiguracion* &config)
    :stacking(config->stacking), retoMas4(config->retoMas4),modoRobo(config->modoRobo), gritoUno(config->gritoUno), ganarNegra(config->ganarNegra), flip(config->flip)
{
    delete config;
    config = nullptr;
    qDebug() << "Se ha eliminado la configuracion ";
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
