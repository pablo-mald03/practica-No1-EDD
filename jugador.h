#ifndef JUGADOR_H
#define JUGADOR_H

//Includes de c++
#include<string>

//Includes de clases propias
#include"listaenlazada.h"
#include"modelo.h"

class Jugador
{

private:

    std::string nombre;
    ListaEnlazada<Modelo*> *mazo;


public:
    Jugador(const std::string _nombre);
    ~Jugador();



};

#endif // JUGADOR_H
