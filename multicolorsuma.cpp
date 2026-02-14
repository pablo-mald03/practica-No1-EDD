#include "multicolorsuma.h"

MultiColorSuma::MultiColorSuma(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::SUMAMULTICOLOR),valorSuma(_valor)  {}

int MultiColorSuma::getValorSuma(){
    return this->valorSuma;
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

//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void MultiColorSuma::lanzarCarta(ListaCircular<Jugador*> & jugador){

}

//Caso donde la carta debe interactuar con la partida
void MultiColorSuma::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void MultiColorSuma::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {

}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


MultiColorSuma::~MultiColorSuma(){

}
