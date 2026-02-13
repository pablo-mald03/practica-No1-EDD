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

//Metodo que se encarga de retornar la informacion principal al iniciar la partida
void PartidaController::iniciarPartida(){
    emit partidaIniciada(this->gestorPartida->getJugadorActual());
}
