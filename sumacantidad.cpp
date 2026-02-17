#include "sumacantidad.h"
#include"jugador.h"
#include"partida.h"
#include"QDebug"

SumaCantidad::SumaCantidad(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado,int _jerarquia, int _valor)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::SUMARCANTIDAD, _jerarquia),valorSuma(_valor)
{

}

//Metodos getters y setters
int SumaCantidad::getValorSuma(){
    return this->valorSuma;
}


//=================APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========


//Metodo donde se requiera mover a la lista de jugadores
void SumaCantidad::lanzarCarta(ListaCircular<Jugador*> & jugador){

}

//Caso donde la carta debe interactuar con la partida
void SumaCantidad::lanzarCarta(Partida & partidaActual) {

}

//Caso donde la carta debe interactuar con la partida y un jugador x
void SumaCantidad::lanzarCarta(Partida & partidaActual, ListaCircular<Jugador*> & jugador) {

    ListaEnlazada<Carta> * listaCartas = jugador.getActual()->getMazo();

    Pila<Carta> * pilaLateral = partidaActual.getPilaLateral();

    for (int i = 0; i < this->valorSuma; i++) {
        if (pilaLateral->estaVacia()) {
            partidaActual.llenarPilaLateral();
        }

        if (pilaLateral->estaVacia()) break;

        Carta cartaDesapilada = pilaLateral->verTop();
        listaCartas->insertarFrente(cartaDesapilada);
        pilaLateral->pop();
    }

}


//=================FIN DEL APARTADO DONDE SE USAN LOS METODOS SOBREESCRITOS DE LAS ACCIONES DE LAS CARTAS========



//Metodo que retorna el valor de imagen de la carta
std::string SumaCantidad::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        if(Modelo::getColor().getColorCarta() == TipoColor::AMARILLO){

            if(this->valorSuma == 1){
                return ":/assets/mediaGame/CartaYMas1.png";
            }
            else if(this->valorSuma == 2){
                return ":/assets/mediaGame/CartaYMas2.png";
            }
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROJO){
            if(this->valorSuma == 1){
                return ":/assets/mediaGame/CartaRMas1.png";
            }
            else if(this->valorSuma == 2){
                return ":/assets/mediaGame/CartaRMas2.png";
            }
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::AZUL){

            if(this->valorSuma == 1){
                return ":/assets/mediaGame/CartaAMas1.png";
            }
            else if(this->valorSuma == 2){
                return ":/assets/mediaGame/CartaAMas2.png";
            }
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::VERDE){
            if(this->valorSuma == 1){
                return ":/assets/mediaGame/CartaVMas1.png";
            }
            else if(this->valorSuma == 2){
                return ":/assets/mediaGame/CartaVMas2.png";
            }
        }

    }else if(Modelo::getLado() == "oscuro"){

        if(Modelo::getColor().getColorCarta() == TipoColor::VIOLETA && this->valorSuma == 3){
            return ":/assets/mediaGame/CartaVIMas3.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::TURQUESA && this->valorSuma == 3){
            return ":/assets/mediaGame/CartaTMas3.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROSA && this->valorSuma == 3){
            return ":/assets/mediaGame/CartaROMas3.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::NARANJA && this->valorSuma == 3){
            return ":/assets/mediaGame/CartaNMas3.png";
        }
    }
    return ":/assets/mediaGame/ReversoCarta.png";
}



SumaCantidad::~SumaCantidad(){

}
