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

    //Atributos que permiten saber si el jugador esta obligado a tirar una carta
    TipoCarta tipoObligado;
    bool estaObligado;

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

    //Metodos que permiten saber si se esta obligado a tirar un color o carta
    TipoCarta getTipoObligado();
    bool getEstaObligado();

    void setTipoObligado(TipoCarta tipo);
    void setEstaObligado(bool flag);

    //Metodo para ordenar cartas
    void ordenarCartas(bool estaEnFlip);

    //Metodos de ordenamiento de datos (propios del jugador CASO REAL)
    int prioridadColor(const Carta& carta,bool estaEnFlip);
    bool menorQue(const Carta& a, const Carta& b,bool estaEnFlip);
    int prioridadJerarquia(const Carta& carta,bool estaEnFlip);

    //Metodo de desorden que permite ejecutar un desorden con la carta eclipse
    void desordenarCartas();

};

#endif // JUGADOR_H
