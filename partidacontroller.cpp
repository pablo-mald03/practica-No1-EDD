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


//Metodo que permite ejecutar la accion y comunicarse con el backend de cuando el jugador en pantalla tira una carta
void PartidaController::tirarCarta(int indice){

    // 1. Ejecutas la lógica: el jugador actual pierde la carta y esta va a la pila
    //bool jugadaValida = this->gestorPartida->ejecutarTirada(indice);
/*
    if (jugadaValida) {
        // 2. REFRESCO INMEDIATO (Muestra al mismo jugador con -1 carta)
        // Como aún NO hemos llamado a avanzarSiguiente(), getJugadorActual() sigue siendo el mismo.
        this->obtenerDatosPartida();

        // 3. CAMBIO INTERNO (Preparamos el backend para el siguiente)
        //this->gestorPartida->avanzarSiguiente();

        // 4. AVISO
        emit darMensaje("Carta lanzada con éxito...");
    } else {

        emit darMensaje("Esa carta no se puede tirar");
    }*/
    reportarMensaje("tilin insano jiji");

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
