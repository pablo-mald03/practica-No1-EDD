#include "bloqueo.h"


Bloqueo::Bloqueo(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CARTABLOQUEO,_jerarquia)
{

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

//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void Bloqueo::lanzarCarta(ListaCircular<Jugador*> & jugador){



}

//Caso donde la carta debe interactuar con la partida
void Bloqueo::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void Bloqueo::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {

    if(partidaActual.getDireccion() == "Derecha"){
        jugador.avanzar();
    }else if (partidaActual.getDireccion() == "Izquierda"){
        jugador.retroceder();
    }
}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========

Bloqueo::~Bloqueo(){

}
