#ifndef JUGADOR_H
#define JUGADOR_H

//Includes de c++
#include<string>

//Includes de clases propias
#include"listaenlazada.h"
#include"carta.h".h"

class Jugador
{

private:

    std::string nombre;
    ListaEnlazada<Carta*> *mazo;

public:
    Jugador(const std::string _nombre);
    ~Jugador();

    //Sobrecarga del operador igual
    bool operator==(const Jugador& otro) const;


};

#endif // JUGADOR_H
