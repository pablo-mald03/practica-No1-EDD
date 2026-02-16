#include "cambiodireccion.h"

CambioDireccion::CambioDireccion(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CAMBIARDIRECCION,_jerarquia)
{

}

//Metodo que retorna el valor de imagen de la carta
std::string CambioDireccion::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        if(Modelo::getColor().getColorCarta() == TipoColor::AMARILLO){
            return ":/assets/mediaGame/CartaYRE.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::AZUL){
            return ":/assets/mediaGame/CartaARE.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::VERDE){
            return ":/assets/mediaGame/CartaVRE.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROJO){
            return ":/assets/mediaGame/CartaRRE.png";
        }
    }else if(Modelo::getLado() == "oscuro"){

        if(Modelo::getColor().getColorCarta() == TipoColor::VIOLETA){
            return ":/assets/mediaGame/CartaVIRE.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROSA){
            return ":/assets/mediaGame/CartaRORE.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::NARANJA){
            return ":/assets/mediaGame/CartaNRE.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::TURQUESA){
            return ":/assets/mediaGame/CartaTRE.png";
        }
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}


//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void CambioDireccion::lanzarCarta(ListaCircular<Jugador*> & jugador){

}

//Caso donde la carta debe interactuar con la partida
void CambioDireccion::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void CambioDireccion::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {
    partidaActual.cambiarDireccion();
}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


CambioDireccion::~CambioDireccion(){

}
