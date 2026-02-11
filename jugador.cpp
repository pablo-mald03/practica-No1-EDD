#include "jugador.h"

Jugador::Jugador(const std::string _nombre): nombre(_nombre)
{
    this->mazo = new ListaEnlazada<Modelo*>();
}

//Apartado de acciones que puede hacer el jugador


//Destructor del objeto
Jugador::~Jugador(){
    delete this->mazo;
}




