#include "jugador.h"

Jugador::Jugador(const std::string _nombre): nombre(_nombre)
{
    this->mazo = new ListaEnlazada<Modelo*>();
}

//Apartado de acciones que puede hacer el jugador


//Sobrecarga del operador igual
bool Jugador::operator==(const Jugador& otro) const{
    return this->nombre == otro.nombre;
}

//Destructor del objeto
Jugador::~Jugador(){
    delete this->mazo;
}




