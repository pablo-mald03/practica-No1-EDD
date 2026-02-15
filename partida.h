#ifndef PARTIDA_H
#define PARTIDA_H

//Includes de C++
#include<string>

//Declaracion del struct usado
struct DatosConfiguracion;

//Includes de las clases propias
#include"listacircular.h"
#include"jugador.h"
#include"configuracionpartida.h"
#include"pila.h"

class Partida
{
private:
    ListaCircular<Jugador*> listaJugadores;
    ConfiguracionPartida configuracion;
    int cantidadJugadores;
    std::string direccion;
    int cantidadVueltas;

    //Arreglos modelo de cartas
    Modelo * modelosClaros[56];
    Modelo * modelosOscuros[56];

    //Lista provisional (UTIL SOLO DURANTE EL TIEMPO DE REVOLVER CARTAS Y AGREGAR)
    ListaEnlazada<Carta> * listadoCartas;

    //LISTADOS TEMPORALES PARA ARMAR LAS INSTANCIAS DEL FLIP
    ListaEnlazada<Carta> * listaCartasBlancas;
    ListaEnlazada<Carta> * listadoCartasOscuras;

    //Pila de las cartas laterales
    Pila<Carta> *pilaLateralCartas;

    //Pila de las cartas laterales
    Pila<Carta> *pilaCentralCartas;

    //Referencia al puntero para contabilizar una vuelta dada
    Nodo<Jugador*> inicioRonda = nullptr;

    //Metodos propios de la clase para hacer funcionar la partida
    void generarJugadores();
    int generarIndiceRandom(int limiteSuperior);
    void correrIndices();

    //Metodo de una sola utilidad
    void generarDireccionInicial();

    //Metodos que permiten generar los modelos de cartas base
    void generarCartasClaras();
    void generarCartasOscuras();

    //Metodos que sirven para armar los modelos de cartas
    void armarCartas();
    void armarCartasNormal(ListaEnlazada<Carta>*& lista);
    void armarCartasFlip(ListaEnlazada<Carta>*& lista);
    //METODOS UNICAMENTE ESPECIALES PARA ARMAR LAS INSTANICAS  DE CADA UNO DE LOS LADOS DEL FLIP
    void armarCartasOscuras(ListaEnlazada<Carta>*& lista);

    //Metodos que sirven para poder barajear y mezclar las cartas
    void barajarCartas(ListaEnlazada<Carta> *& lista);


    //Metodo para limpiar las cosas en el destructor
    void limpiarReferencias();

    //Metodo que permite repartir a cada jugador las cartas YA REVUELTAS
    void repartirCartas();
    //Metodo que le dice a todos los jugadores que ordenen sus cartas
    void ordenCartas();



public:
    Partida(int _cantidadJugadores,DatosConfiguracion* &config);
    ~Partida();


    //Apartado de comunicacion de backend con las acciones que deba ejecutar frontend
    Jugador* & getJugadorActual();

    //Metodo que permite obtener la direccion
    std::string getDireccion();
    //Metodos que permiten mostrar en la UI los datos de vuelta y de cantidad de cartas en la pila
    int getCantidadPila();
    int getCantidadVueltas();
};

/*CREATED BY PABLO M*/

#endif // PARTIDA_H
