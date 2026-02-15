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

    //Metodo que permite obtener el mazo
    ListaEnlazada<Carta> * getMazo();

    //Metodo para ordenar cartas
    void ordenarCartas();

    //Metodos de ordenamiento de datos (propios del jugador CASO REAL)
    int prioridadColor(const Carta& carta);
    bool menorQue(const Carta& a, const Carta& b);
    int prioridadJerarquia(const Carta& carta);

};

#endif // JUGADOR_H
