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

struct ResultadoJugada {

    bool jugadaValida = false;
    bool darMensaje = false;
    std::string mensajeJugador;
    int tiempoMensaje = 0;
    int tiempoAnimacion = 0;
    bool requiereDecision = false;
};

class Partida
{
private:
    ListaCircular<Jugador*> listaJugadores;
    ConfiguracionPartida configuracion;
    int cantidadJugadores;
    std::string direccion;
    int cantidadVueltas;

    //Flag que permite saber si se puede mover
    bool puedeMoverse;

    //Flag que permite saber si se cambio al lado flip
    bool estaFlip;

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

    //Metodo para verificar si ya se dio una vuelta
    void verificarVuelta();

    //Metodo para limpiar las cosas en el destructor
    void limpiarReferencias();

    //Metodo que permite repartir a cada jugador las cartas YA REVUELTAS
    void repartirCartas();
    //Metodo que le dice a todos los jugadores que ordenen sus cartas
    void ordenCartas();

    //Metodos privados que permiten verificar colores y numeros en base a la jerarquia
    bool tieneEnClaras();
    bool tieneEnOscuras();

    //Metodos para verificar la jerarquia y el color de la carta
    bool esMismaClara(const Carta& cartaJugador, const Carta& cartaPila);
    bool esMismaOscura(const Carta& cartaJugador, const Carta& cartaPila);

    //Metodo para ejecutar las acciones de las cartas claras y oscuras
    ResultadoJugada ejecutarAccionCartaClara(int indice);
    ResultadoJugada ejecutarAccionCartaOscura(int indice);


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
    std::string imagenPilaCentral();
    std::string imagenPilaLateral();

    //Permite pasar al siguiente jugador
    void ejecutarMovimiento();


    //Metodo UNICO QUE PERMITE INTERACTUAR CON TODA LA LOGICA DEL BACKEND
    ResultadoJugada ejecutarTirada(int indice);

    //Metodos getters y setters
    bool getPuedeMoverse();
    void setPuedeMoverse(bool accion);

    bool getEstaFlip();
    void setEstaFlip(bool accion);

    //Metodo de verificacion para saber si tiene carta del mismo color o mismo numero
    bool tieneCartaNecesaria();

    //Metodo ejecutado cuando un jugador toma una carta y la agrega a su mazo
    bool tomarCarta();

};

/*CREATED BY PABLO M*/

#endif // PARTIDA_H
