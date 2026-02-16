#include "eclipse.h"

Eclipse::Eclipse(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CARTAECLIPSE,_jerarquia)
{

}

//Metodo que retorna el valor de imagen de la carta
std::string Eclipse::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        return ":/assets/mediaGame/CartaEcplipse.png";
    }else if(Modelo::getLado() == "oscuro"){
        return ":/assets/mediaGame/CartaEcplipseNegra.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}

//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void Eclipse::lanzarCarta(ListaCircular<Jugador*> & jugador){

}

//Caso donde la carta debe interactuar con la partida
void Eclipse::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void Eclipse::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {

}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


Eclipse::~Eclipse(){

}
