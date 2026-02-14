#include "reversa.h"

Reversa::Reversa(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::Reverse)
{

}


//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void Reversa::lanzarCarta(ListaCircular<Jugador*> & jugador){

}

//Caso donde la carta debe interactuar con la partida
void Reversa::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void Reversa::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {

}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo que retorna el valor de imagen de la carta
std::string Reversa::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        if(Modelo::getColor().getColorCarta() == TipoColor::AMARILLO){
            return ":/assets/mediaGame/CartaYVolteo.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROJO){
            return ":/assets/mediaGame/CartaRvolteo.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::AZUL){
            return ":/assets/mediaGame/CartaAVolteo.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::VERDE){
            return ":/assets/mediaGame/CartaVVolteo.png";
        }

    }else if(Modelo::getLado() == "oscuro"){

        if(Modelo::getColor().getColorCarta() == TipoColor::VIOLETA){
            return ":/assets/mediaGame/CartaVIVolteo.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::TURQUESA){
            return ":/assets/mediaGame/CartaTVolteo.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROSA){
            return ":/assets/mediaGame/CartaROVolteo.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::NARANJA){
            return ":/assets/mediaGame/CartaNVolteo.png";
        }
    }
    return ":/assets/mediaGame/ReversoCarta.png";
}

Reversa::~Reversa(){

}
