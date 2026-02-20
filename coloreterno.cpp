#include "coloreterno.h"
#include"partida.h"
#include"jugador.h"

ColorEterno::ColorEterno(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::ETERNA,_jerarquia) {}


//Metodo que retorna el valor de imagen de la carta
std::string ColorEterno::getPathImagen() const{

    if(Modelo::getLado() == "oscuro"){
        return ":/assets/mediaGame/CartaColorEterno.png";
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}

//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void ColorEterno::lanzarCarta(ListaCircular<Jugador*> & jugador){

}

//Caso donde la carta debe interactuar con la partida
void ColorEterno::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void ColorEterno::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {

    Jugador * jugadorSiguiente = partidaActual.pickJugadorSiguiente();
    jugadorSiguiente->setObligadoSacar(true);
}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


ColorEterno::~ColorEterno(){

}
