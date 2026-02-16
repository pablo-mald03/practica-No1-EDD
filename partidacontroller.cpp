#include "partidacontroller.h"
#include <qdebug.h>

PartidaController::PartidaController(int _cantidad,bool &estaConfigurando, DatosConfiguracion * &config, QObject* parent)
    :QObject(parent)
{

    estaConfigurando = false;
    this->gestorPartida= new Partida(_cantidad,config);
}

PartidaController::~PartidaController(){

    delete this->gestorPartida;
    this->gestorPartida = nullptr;
}

bool PartidaController::estaModoFlip(){
    return this->gestorPartida->getEstaFlip();
}


//Metodo que permite ejecutar la accion y comunicarse con el backend de cuando el jugador en pantalla tira una carta
void PartidaController::tirarCarta(int indice){


    try{
        //Metodo principal
        bool jugadaNormal = this->gestorPartida->ejecutarTirada(indice);

        if (jugadaNormal) {

            //Acciones antes de refrescar
            this->obtenerDatosPartida();

            this->gestorPartida->ejecutarMovimiento();

            if(!this->gestorPartida->getPuedeMoverse()){
                this->gestorPartida->setPuedeMoverse(true);
            }

        } else {
           reportarMensaje("Esa carta no se puede tirar");
        }

    }catch(const std::runtime_error & ex){
        reportarMensaje(ex.what());
    }

}
//Metodo util para verificar si puede desapilar
bool PartidaController::puedeDesapilar(){
    return this->gestorPartida->tieneCartaNecesaria();
}

//Metodo utilzado para que el usuario pueda desapilar una carta
void PartidaController::desapilarCarta(){

    bool cartaDesapilada = this->gestorPartida->tomarCarta();

    if(cartaDesapilada){
        this->obtenerDatosPartida();
    }else{
        throw std::runtime_error("La pila de cartas ya esta vacia");
    }

}


//Metodo que permite soltar mensajes en la ui de avisos
void PartidaController::reportarMensaje(std::string mensaje){
    emit darMensaje(mensaje);
}

//Metodo que se encarga de retornar la informacion principal al iniciar la partida
void PartidaController::obtenerDatosPartida(){
    emit datosPartida(this->gestorPartida->getJugadorActual(),this->gestorPartida->getDireccion(), this->gestorPartida->getCantidadPila(), this->gestorPartida->getCantidadVueltas());
    emit datosPilaCentral(this->gestorPartida->imagenPilaCentral());
    emit datosPilaLateral(this->gestorPartida->imagenPilaLateral(), this->gestorPartida->getCantidadPila());

}
