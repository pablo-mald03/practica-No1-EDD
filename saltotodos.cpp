#include "saltotodos.h"
#include"partida.h"
#include"jugador.h"

SaltoTodos::SaltoTodos(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::SALTOTOTAL,_jerarquia)
{

}


//Metodo que retorna el valor de imagen de la carta
std::string SaltoTodos::getPathImagen() const{

    if(Modelo::getColor().getColorCarta() == TipoColor::TURQUESA){
        return ":/assets/mediaGame/CartaTSalto.png";
    }
    else if(Modelo::getColor().getColorCarta() == TipoColor::VIOLETA){
        return ":/assets/mediaGame/CartaVISalto.png";
    }
    else if(Modelo::getColor().getColorCarta() == TipoColor::ROSA){
        return ":/assets/mediaGame/CartaROSalto.png";
    }
    else if(Modelo::getColor().getColorCarta() == TipoColor::NARANJA){
        return ":/assets/mediaGame/CartaNSalto.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}

//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void SaltoTodos::lanzarCarta(ListaCircular<Jugador*> & jugador){

}

//Caso donde la carta debe interactuar con la partida
void SaltoTodos::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void SaltoTodos::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {

    for (int i = 0; i < jugador.getLongitud(); i++) {
        partidaActual.ejecutarMovimiento();
    }
}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========

SaltoTodos::~SaltoTodos(){

}
