#ifndef JUGADOR_H
#define JUGADOR_H

//Includes de c++
#include<string>

//Includes de clases propias
#include"listaenlazada.h"
#include"carta.h"

class Jugador
{

private:

    int codigo;
    std::string nombre;
    ListaEnlazada<Carta> *mazo;

public:
    Jugador(const std::string _nombre, int codigo);
    ~Jugador();

    //Sobrecarga del operador igual
    bool operator==(const Jugador& otro) const;

    int getCodigo()const;
    int getIndice()const;
    std::string getNombre()const;

};

#endif // JUGADOR_H
