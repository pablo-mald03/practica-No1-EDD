#include "partidacontroller.h"

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

void PartidaController::iniciar(){

}
