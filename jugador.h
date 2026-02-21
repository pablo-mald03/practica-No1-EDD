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

    //Atributo que permite saber si el jugador esta obligado a sacar caratas hasta un color
    bool obligadoSacar;
    TipoColor colorObligado;

    //Flag que permite determinar si el jugador esta propenso a quedar en UNO
    bool propensoUno;

    //Flag que le permite al jugador declararse en UNO
    bool dijoUno;

public:
    Jugador(const std::string _nombre, int codigo);
    //Constructor copia
    Jugador(const Jugador& otro);
    ~Jugador();

    //Sobrecarga del operador igual
    bool operator==(const Jugador& otro) const;

    int getCodigo()const;
    int getIndice()const;
    std::string getNombre()const;

    //Metodo que permite obtener el mazo
    ListaEnlazada<Carta> * getMazo();

    //===========REGION Metodos que permiten saber si se esta obligado a tirar un color o carta
    TipoCarta getTipoObligado();
    bool getEstaObligado();
    void setTipoObligado(TipoCarta tipo);
    void setEstaObligado(bool flag);
    //===========REGION Metodos que permiten saber si se esta obligado a tirar un color o carta


    //========REGION Metodos que permiten saber si el jugador esta obligado a sacar un color
    TipoColor getColorObligado();
    bool getObligadoSacar();
    void setColorObligado(TipoColor tipo);
    void setObligadoSacar(bool flag);

    //========REGION Metodos que permiten saber si el jugador esta obligado a sacar un color

    //Metodo para ordenar cartas
    void ordenarCartas(bool estaEnFlip);

    //Metodos de ordenamiento de datos (propios del jugador CASO REAL)
    int prioridadColor(const Carta& carta,bool estaEnFlip);
    bool menorQue(const Carta& a, const Carta& b,bool estaEnFlip);
    int prioridadJerarquia(const Carta& carta,bool estaEnFlip);

    //Metodo de desorden que permite ejecutar un desorden con la carta eclipse
    void desordenarCartas();
    //Metodo que permite saber el color al que esta obligado a sacar el jugador
    std::string saberColorObligado(TipoColor colorCarta);

    //Metodo que permite saber si esta en UNO
    bool faltaUna();

    //Metodo que permite autoevaluar si el jugador esta propenso a quedarse a UNO
    void evaluarPropensoUno();

    //Metodo que permite evaluar si el jugador actual esta propenso a uno (PARA PODER ACTIVAR EL BOTON)
    bool estaPropensoUno();
    /*===========Region de metodos getter y setter para saber si el jugador dijo UNO*/
    void setDijoUno(bool flag);
    bool getDijoUno();
    /*===========Region de metodos getter y setter para saber si el jugador dijo UNO*/

};

#endif // JUGADOR_H
