#include "partida.h"
#include "bloqueo.h"
#include "cambiodireccion.h"
#include "coloreterno.h"
#include "comodincolor.h"
#include "eclipse.h"
#include "espia.h"
#include"mainwindow.h"
#include "modelo.h"
#include "multicolorsuma.h"
#include"numerica.h"
#include "saltotodos.h"
#include "sumacantidad.h"
#include <QRandomGenerator>

/*CREATED BY PABLO M*/

Partida::Partida(int _cantidadJugadores,DatosConfiguracion* &config)
    :cantidadJugadores(_cantidadJugadores),listaJugadores(), configuracion(config), direccion("Derecha")
{
    generarJugadores();
    delete config;
    config = nullptr;

    correrIndices();
    generarDireccionInicial();
    generarCartasClaras();
    generarCartasOscuras();
}



std::string Partida::getDireccion(){
    return this->direccion;
}

//==============FIN DEL APARTADO DE METODOS GETTER DE LA CLASE===================


//Metodo de una sola utilidad
void Partida::generarDireccionInicial(){
    int opcion = generarIndiceRandom(10);
    if(opcion > 4){
        this->direccion = "Derecha";
    }else{
        this->direccion = "Izquierda";
    }
}

//Metodo que permite correr el indice de la lista para tener un inicio aleatorio
void Partida::correrIndices(){
    int limite = generarIndiceRandom(this->listaJugadores.getLongitud());

    for (int i = 0; i <= limite; ++i) {
        this->listaJugadores.avanzar();
    }
}

//Metodo para generar los jugadores de la partida
void Partida::generarJugadores(){
    for (int i = 0; i < this->cantidadJugadores; ++i) {
        this->listaJugadores.insertar(new Jugador("Jugador " + std::to_string(i + 1), i));
    }
}

//Metodo que genera un metodoRandom
int Partida::generarIndiceRandom(int limiteSuperior) {
    return QRandomGenerator::global()->bounded(limiteSuperior+1);
}

Jugador* & Partida::getJugadorActual(){
    return this->listaJugadores.getActual();
}


//==============APARTADO DE METODOS DE GENERACION DE CARTAS DEL JUEGO===================
void Partida::generarCartasClaras(){

    std::string arregloNombres [] = {"cero","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"};

    int j = 0;
    //=======INICIALIZACION CARTAS NUMERICAS=====
    //Inicializacion de cartas numericas rojas

    for (int i = 0; i < 10; ++i) {
        this->modelosClaros[i] = new Numerica(ColorCarta(TipoColor::ROJO),arregloNombres[j],"claro",j);
        j++;
    }

    j = 0;
    //Inicializacion de cartas numericas amarillas
    for (int i = 10; i < 20; ++i) {
        this->modelosClaros[i] = new Numerica(ColorCarta(TipoColor::AMARILLO),arregloNombres[j],"claro",j);
    }

    j = 0;
    //Inicializacion de cartas numericas verdes
    for (int i = 20; i < 30; ++i) {
        this->modelosClaros[i] = new Numerica(ColorCarta(TipoColor::VERDE),arregloNombres[j],"claro",j);
    }
    j = 0;
    //Inicializacion de cartas numericas azules
    for (int i = 30; i < 40; ++i) {
        this->modelosClaros[i] = new Numerica(ColorCarta(TipoColor::AZUL),arregloNombres[j],"claro",j);
    }

    //=======FIN INICIALIZACION CARTAS NUMERICAS=====

    //Generacion de cartas de sumar cantidad
    if(!this->configuracion.esFlip()){
        this->modelosClaros[40] = new SumaCantidad(ColorCarta(TipoColor::AZUL),"Mas dos Azul","claro",2);
        this->modelosClaros[41] = new SumaCantidad(ColorCarta(TipoColor::AMARILLO),"Mas dos Amarillo","claro",2);
        this->modelosClaros[42] = new SumaCantidad(ColorCarta(TipoColor::ROJO),"Mas dos Rojo","claro",2);
        this->modelosClaros[43] = new SumaCantidad(ColorCarta(TipoColor::VERDE),"Mas dos Verde","claro",2);
    }else{
        this->modelosClaros[40] = new SumaCantidad(ColorCarta(TipoColor::AZUL),"Mas dos Azul","claro",1);
        this->modelosClaros[41] = new SumaCantidad(ColorCarta(TipoColor::AMARILLO),"Mas dos Amarillo","claro",1);
        this->modelosClaros[42] = new SumaCantidad(ColorCarta(TipoColor::ROJO),"Mas dos Rojo","claro",1);
        this->modelosClaros[43] = new SumaCantidad(ColorCarta(TipoColor::VERDE),"Mas dos Verde","claro",1);
    }

    //Generacion de cartas de cambio de direccion
    this->modelosClaros[44] = new CambioDireccion(ColorCarta(TipoColor::AZUL),"Cambio direccion Azul","claro");
    this->modelosClaros[45] = new CambioDireccion(ColorCarta(TipoColor::AMARILLO),"Cambio direccion Amarillo","claro");
    this->modelosClaros[46] = new CambioDireccion(ColorCarta(TipoColor::ROJO),"Cambio direccion Rojo","claro");
    this->modelosClaros[47] = new CambioDireccion(ColorCarta(TipoColor::VERDE),"Cambio direccion Verde","claro");

    //Generacion de cartas de bloqueo
    this->modelosClaros[48] = new Bloqueo(ColorCarta(TipoColor::AZUL),"Bloqueo Azul","claro");
    this->modelosClaros[49] = new Bloqueo(ColorCarta(TipoColor::AMARILLO),"Bloqueo Amarillo","claro");
    this->modelosClaros[50] = new Bloqueo(ColorCarta(TipoColor::ROJO),"Bloqueo Rojo","claro");
    this->modelosClaros[51] = new Bloqueo(ColorCarta(TipoColor::VERDE),"Bloqueo Verde","claro");

    //Generacion de cartas multicolor comodin suma
    if(!this->configuracion.esFlip()){
        this->modelosClaros[52] = new MultiColorSuma(ColorCarta(TipoColor::MULTICOLOR),"Multicolor mas 4","claro",4);
    }else{
        this->modelosClaros[52] = new MultiColorSuma(ColorCarta(TipoColor::MULTICOLOR),"Multicolor mas 2","claro",2);
    }

    //Generacion de la carta comodin
    this->modelosClaros[53] = new ComodinColor(ColorCarta(TipoColor::MULTICOLOR),"Comodin","claro");

    //Carta eclipse MIA
    this->modelosClaros[54] = new Eclipse(ColorCarta(TipoColor::PREDETERMINADO),"Eclipse","claro");

    //Carta eclipse ESPIA
    this->modelosClaros[55] = new Espia(ColorCarta(TipoColor::PREDETERMINADO),"Espia","claro");

}

//Metodo que permite generar las cartas negras cuando se requieren
void Partida::generarCartasOscuras(){

    if(!this->configuracion.esFlip()){
        return;
    }

    std::string arregloNombres [] = {"cero","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"};

    int j = 0;
    //=======INICIALIZACION CARTAS NUMERICAS=====
    //Inicializacion de cartas numericas rojas

    for (int i = 0; i < 10; ++i) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::ROSA),arregloNombres[j],"oscuro",j);
        j++;
    }

    j = 0;
    //Inicializacion de cartas numericas amarillas
    for (int i = 10; i < 20; ++i) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::NARANJA),arregloNombres[j],"oscuro",j);
    }

    j = 0;
    //Inicializacion de cartas numericas verdes
    for (int i = 20; i < 30; ++i) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::TURQUESA),arregloNombres[j],"oscuro",j);
    }
    j = 0;
    //Inicializacion de cartas numericas azules
    for (int i = 30; i < 40; ++i) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::VIOLETA),arregloNombres[j],"oscuro",j);
    }

    //=======FIN INICIALIZACION CARTAS NUMERICAS=====


    //Generacion de las cartas oscuras +3
    this->modelosOscuros[40] = new SumaCantidad(ColorCarta(TipoColor::ROSA),"Mas tres Rosa","oscuro",3);
    this->modelosOscuros[41] = new SumaCantidad(ColorCarta(TipoColor::NARANJA),"Mas tres Naranja","oscuro",3);
    this->modelosOscuros[42] = new SumaCantidad(ColorCarta(TipoColor::VIOLETA),"Mas tres Violeta","oscuro",3);
    this->modelosOscuros[43] = new SumaCantidad(ColorCarta(TipoColor::TURQUESA),"Mas tres Turquesa","oscuro",3);

    //Generacion de cartas de cambio de direccion
    this->modelosOscuros[44] = new CambioDireccion(ColorCarta(TipoColor::ROSA),"Cambio direccion Rosa","oscuro");
    this->modelosOscuros[45] = new CambioDireccion(ColorCarta(TipoColor::NARANJA),"Cambio direccion Naranja","oscuro");
    this->modelosOscuros[46] = new CambioDireccion(ColorCarta(TipoColor::VIOLETA),"Cambio direccion Violeta","oscuro");
    this->modelosOscuros[47] = new CambioDireccion(ColorCarta(TipoColor::TURQUESA),"Cambio direccion Turquesa","oscuro");

    //Modelo de salto a todos
    this->modelosOscuros[48] = new SaltoTodos(ColorCarta(TipoColor::ROSA),"Salto Todos Rosa","oscuro");
    this->modelosOscuros[49] = new SaltoTodos(ColorCarta(TipoColor::NARANJA),"Salto Todos Naranja","oscuro");
    this->modelosOscuros[50] = new SaltoTodos(ColorCarta(TipoColor::VIOLETA),"Salto Todos Violeta","oscuro");
    this->modelosOscuros[51] = new SaltoTodos(ColorCarta(TipoColor::TURQUESA),"Salto Todos Turquesa","oscuro");

    //Modelo de comodin +6
    this->modelosOscuros[52] = new MultiColorSuma(ColorCarta(TipoColor::MULTICOLOR),"Multicolor mas 6","oscuro",6);

    //Modelo de comodin Color eterno
    this->modelosOscuros[53] = new ColorEterno(ColorCarta(TipoColor::PREDETERMINADO),"Color Eterno","oscuro");

    //Carta eclipse MIA (P)
    this->modelosOscuros[54] = new Eclipse(ColorCarta(TipoColor::PREDETERMINADO),"Eclipse","oscuro");

    //Carta eclipse ESPIA (P)
    this->modelosOscuros[55] = new Espia(ColorCarta(TipoColor::PREDETERMINADO),"Espia","oscuro");
}

//==============FIN DEL APARTADO DE METODOS DE GENERACION DE CARTAS DEL JUEGO===================


Partida::~Partida(){

}

//CREATED BY (P.M)

