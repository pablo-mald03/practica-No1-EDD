#include "jugador.h"
#include"bloqueo.h"
#include"colorcarta.h"
#include"QDebug"

Jugador::Jugador(const std::string _nombre, int _codigo): nombre(_nombre), codigo(_codigo)
{
    this->mazo = new ListaEnlazada<Carta>();

    int indice = this->mazo->getLongitud();

    this->mazo->insertar(indice,Carta(
                                      Bloqueo(ColorCarta("rojo"),"Bloqueo","atras"), Bloqueo(ColorCarta("rojo"),"Bloqueo","frente"), indice));
}

//Apartado de acciones que puede hacer el jugador


//Sobrecarga del operador igual
bool Jugador::operator==(const Jugador& otro) const{
    return this->nombre == otro.nombre && this->codigo == otro.codigo;
}

//Metodos getters y setters
int Jugador::getCodigo()const{
    return this->codigo + 1;
}

int Jugador::getIndice()const{
    return this->codigo;
}


std::string Jugador::getNombre()const{
    return this->nombre;
}

//Metodo que permite obtener el mazo del jugador
ListaEnlazada<Carta> * Jugador::getMazo(){
    return this->mazo;
}


//Destructor del objeto
Jugador::~Jugador(){
    delete this->mazo;
}




