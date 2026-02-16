#include "espia.h"

Espia::Espia(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia)
    :Modelo(_colorRef,_nombre,_lado, TipoCarta::CARTAESPIA, _jerarquia)
{

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

//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void Espia::lanzarCarta(ListaCircular<Jugador*> & jugador){

}

//Caso donde la carta debe interactuar con la partida
void Espia::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void Espia::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {

}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


Espia::~Espia(){

}

