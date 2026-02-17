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
ResultadoJugada PartidaController::tirarCarta(int indice){


    try{
        //Metodo principal
        ResultadoJugada jugadaNormal = this->gestorPartida->ejecutarTirada(indice);

        if (jugadaNormal.jugadaValida) {

            //Acciones antes de refrescar
            this->obtenerDatosPartida();

            this->gestorPartida->ejecutarMovimiento();

            bool puedeMoverse =this->gestorPartida->getPuedeMoverse();

            if(!puedeMoverse){
                this->gestorPartida->setPuedeMoverse(true);
            }

            if(jugadaNormal.darMensaje){
                QString color = QString::fromStdString(jugadaNormal.colorAviso);
               reportarMensaje(jugadaNormal.mensajeJugador, color, jugadaNormal.tiempoMensaje);
            }

            return jugadaNormal;

        } else {
           reportarMensaje("Esa carta no se puede tirar", "#91042B", 2500);
        }

    }catch(const std::runtime_error & ex){
        reportarMensaje(ex.what(), "#91042B", 2500);
    }

    ResultadoJugada jugadaNormal;
    jugadaNormal.jugadaValida = false;

    return jugadaNormal;
}
//Metodo util para verificar si puede desapilar
bool PartidaController::puedeDesapilar(){
    return this->gestorPartida->tieneCartaNecesaria();
}

//Metodo utilzado para que el usuario pueda desapilar una carta
ResultadoJugada PartidaController::desapilarCarta(){

    ResultadoJugada resultadoJugada = this->gestorPartida->tomarCarta();

    if(resultadoJugada.jugadaValida){
        this->obtenerDatosPartida();
        return resultadoJugada;

    }else{
        throw std::runtime_error("La pila de cartas ya esta vacia");
    }
}


//Metodo que permite soltar mensajes en la ui de avisos
void PartidaController::reportarMensaje(std::string mensaje, QString colorHex, int tiempo){
    emit darMensaje(mensaje,colorHex, tiempo);
}

//Metodo que se encarga de retornar la informacion principal al iniciar la partida
void PartidaController::obtenerDatosPartida(){
    emit datosPartida(this->gestorPartida->getJugadorActual(),this->gestorPartida->getDireccion(), this->gestorPartida->getCantidadPila(), this->gestorPartida->getCantidadVueltas());
    emit datosPilaCentral(this->gestorPartida->imagenPilaCentral());
    emit datosPilaLateral(this->gestorPartida->imagenPilaLateral(), this->gestorPartida->getCantidadPila());

}
