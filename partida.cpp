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
    :cantidadJugadores(_cantidadJugadores),listaJugadores(), configuracion(config), direccion("Derecha"), cantidadVueltas(0), estaFlip(false), puedeMoverse(true)
{
    generarJugadores();
    delete config;
    config = nullptr;

    correrIndices();
    generarDireccionInicial();
    generarCartasClaras();
    generarCartasOscuras();
    armarCartas();

    repartirCartas();
    ordenCartas();

}


//==============APARTADO DE METODOS PARA REPARTIR LAS CARTAS A LOS JUGADORES===================
//Metodo encargado de repartir las cartas complejidad O(n)
void Partida::repartirCartas(){

    this->inicioRonda = this->listaJugadores.getActual();
    int totalCartasRepartir = this->listaJugadores.getLongitud() * 8;

    for (int j = 0; j < totalCartasRepartir; j++) {

        if (!this->pilaLateralCartas->estaVacia()) {
            this->listaJugadores.getActual()->getMazo()->insertarFrente(this->pilaLateralCartas->verTop());
            this->pilaLateralCartas->pop();
        }

        this->listaJugadores.avanzar();
    }
}

//Metodo que avisa a cada jugador que ordene sus propias cartas (METODOS DELEGADOS)
void Partida::ordenCartas(){
    int totalJugadores = this->listaJugadores.getLongitud();
    for (int i = 0; i < totalJugadores; i++) {
        this->listaJugadores.getActual()->ordenarCartas(this->estaFlip);
        this->listaJugadores.avanzar();
    }

    //Saca la primera carta

    Carta cartaInicial = this->pilaLateralCartas->verTop();
    this->pilaCentralCartas->push(cartaInicial);
    this->pilaLateralCartas->pop();
}


//==============APARTADO DE METODOS QUE PERMITEN RESPONDER A LAS ACCIONES DEL JUGADOR===================


//Metodo que sirve para cambiar la direccion (reversa)
void Partida::cambiarDireccion(){

    if(this->getDireccion() == "Derecha"){
        this->direccion = "Izquierda";
    }else if (this->getDireccion() == "Izquierda"){
        this->direccion = "Derecha";
    }
}

//Metodo que permite avanzar en la direccion indicada
void Partida::moverJugador(){
    if(this->getDireccion() == "Derecha"){
        this->listaJugadores.avanzar();
    }else if (this->getDireccion() == "Izquierda"){
        this->listaJugadores.retroceder();
    }
}


ResultadoJugada Partida::tomarCarta(){

    ResultadoJugada resultado;

    try{

        Carta cartaTomada = this->pilaLateralCartas->verTop();

        this->listaJugadores.getActual()->getMazo()->insertarFrente(cartaTomada);
        this->pilaLateralCartas->pop();

        this->listaJugadores.getActual()->ordenarCartas(this->estaFlip);

       // if(this->configuracion.esModoRobo())

        resultado.jugadaValida = true;
        return resultado;

        /*

        resultado.tiempoAnimacion = 2500;
        resultado.tiempoMensaje = 2000;
        resultado.darMensaje = true;
        resultado.colorAviso = "#0C7527";
        resultado.mensajeJugador = ""
        */


    }catch(const std::runtime_error & ex){
        resultado.jugadaValida = false;
        return resultado;
    }
}

//Metodo que permite verificar si el jugador puede ganar con una carta negra
bool Partida::puedeGanarConNegra(int indice){

    bool tieneUltima = this->esUltimaCarta(this->getJugadorActual());

    bool puedeGanarNegra  = this->configuracion.esGanarNegra();

    if(tieneUltima && !this->estaFlip && !puedeGanarNegra){

        Modelo * cartaActual = this->getJugadorActual()->getMazo()->getValor(indice).getAnverso();

        if(cartaActual->getJerarquia() > 12){

            return false;
        }

    } else if(tieneUltima && this->estaFlip && !puedeGanarNegra){

        Modelo * cartaActual = this->getJugadorActual()->getMazo()->getValor(indice).getReverso();

        if(cartaActual->getJerarquia() > 12){
            return false;
        }
    }

    return true;
}

//Metodo que permite ejecutar la tirada
ResultadoJugada Partida::ejecutarTirada(int indice){

    bool puedeTirar = this->tieneCartaNecesaria();
    if(!puedeTirar){
        throw std::runtime_error("No tienes cartas para poder tirar. Saca de la pila");
    }

    bool puedeGanar = this->puedeGanarConNegra(indice);
    if(!puedeGanar){

        ResultadoJugada resultadoTirada;
        resultadoTirada.darMensaje = true;
        resultadoTirada.tiempoMensaje = 1500;
        resultadoTirada.mensajeJugador = std::string("Configuracion activada. NO PUEDES GANAR CON CARTA NEGRA ") ;
        resultadoTirada.colorAviso = "#91042B";
        resultadoTirada.tiempoAnimacion = 2000;
        resultadoTirada.jugadaValida = false;
        return resultadoTirada;
    }

    Carta cartaElegida = this->listaJugadores.getActual()->getMazo()->verValor(indice);

    Carta cartaSuperior = this->pilaCentralCartas->verTop();

    if(!this->estaFlip){

        //Caso de uno cuando no esta en flip
        if(cartaElegida.getAnverso()->getJerarquia()< 13){

            bool coincide = this->esMismaClara(cartaElegida,cartaSuperior);

            if(coincide){
                return this->ejecutarAccionCartaClara(indice);

            }else{
                throw std::runtime_error("El color ni en valor de la carta coinciden");
            }

        }else{
            //PENDIENTE LAS ESPECIALES


        }

    }else{

        //Caso cuando se activo el flip (se dio la vuelta)
        if(cartaElegida.getReverso()->getJerarquia()< 13){

            bool coincide = this->esMismaOscura(cartaElegida,cartaSuperior);

            if(coincide){
                return this->ejecutarAccionCartaOscura(indice);

            }else{
                throw std::runtime_error("El color ni en valor de la carta coinciden");
            }

        }else{
            //PENDIENTE LAS ESPECIALES

        }

    }

    throw std::runtime_error("No se pudo ejecutar la tirada");
}

//Metodo utilizado para ejecutar la accion de cada carta clara
ResultadoJugada Partida::ejecutarAccionCartaClara(int indice){

    Carta cartaElegida = this->listaJugadores.getActual()->getMazo()->verValor(indice);

    ColorCarta color = cartaElegida.getAnverso()->getColor().getColorCarta();

    ResultadoJugada resultadoTirada;

    if(cartaElegida.getAnverso()->getJerarquia() <= 9 ){

        resultadoTirada.darMensaje = true;
        resultadoTirada.tiempoMensaje = 1500;
        resultadoTirada.mensajeJugador = std::string("Se ha tirado la carta ") + cartaElegida.getAnverso()->getNombre();

        this->pilaCentralCartas->push(cartaElegida);
        this->listaJugadores.getActual()->getMazo()->eliminar(indice);

        resultadoTirada.tiempoAnimacion = 2000;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.colorAviso = "#0C7527";
        return resultadoTirada;
    }

    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::CARTABLOQUEO && cartaElegida.getAnverso()->getJerarquia() == 10){

        resultadoTirada.darMensaje = true;
        resultadoTirada.tiempoMensaje = 3000;

        if(this->direccion == "Derecha"){
            resultadoTirada.mensajeJugador = std::string("Se ha tirado la carta ") + cartaElegida.getAnverso()->getNombre() + std::string(" al ") + this->listaJugadores.pickSiguiente()->getNombre();

            cartaElegida.getAnverso()->lanzarCarta(*this,this->listaJugadores);

            this->pilaCentralCartas->push(cartaElegida);
            this->listaJugadores.pickAnterior()->getMazo()->eliminar(indice);

        }else if (this->direccion == "Izquierda"){
            resultadoTirada.mensajeJugador = std::string("Se ha tirado la carta ") + cartaElegida.getAnverso()->getNombre() + std::string(" al ") + this->listaJugadores.pickAnterior()->getNombre();
            cartaElegida.getAnverso()->lanzarCarta(*this,this->listaJugadores);
            this->pilaCentralCartas->push(cartaElegida);
            this->listaJugadores.pickSiguiente()->getMazo()->eliminar(indice);
        }

        resultadoTirada.tiempoAnimacion = 2000;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.colorAviso = "#0C7527";
        return resultadoTirada;
    }

    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::CAMBIARDIRECCION && cartaElegida.getAnverso()->getJerarquia() == 11){

        resultadoTirada.darMensaje = true;
        resultadoTirada.tiempoMensaje = 3000;
        resultadoTirada.mensajeJugador = std::string("El ")+ this->listaJugadores.getActual()->getNombre() + std::string(" tiro la carta ") + cartaElegida.getAnverso()->getNombre() ;

        cartaElegida.getAnverso()->lanzarCarta(*this,this->listaJugadores);
        this->pilaCentralCartas->push(cartaElegida);
        this->listaJugadores.getActual()->getMazo()->eliminar(indice);
        this->setPuedeMoverse(false);

        resultadoTirada.tiempoAnimacion = 2000;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.colorAviso = "#0C7527";

        return resultadoTirada;
    }


    resultadoTirada.colorAviso = "#91042B";
    resultadoTirada.jugadaValida = false;
    return resultadoTirada;
}

//Metodo que permite saber si un jugador ya solo tiene una carta
bool Partida::esUltimaCarta(Jugador * jugadorActual){
    int longitud = jugadorActual->getMazo()->getLongitud();
    return longitud == 1;
}

//Metodo utilizado para ejecutar la accion de cada carta oscura
ResultadoJugada Partida::ejecutarAccionCartaOscura(int indice){

    Carta cartaElegida = this->listaJugadores.getActual()->getMazo()->verValor(indice);

    ColorCarta color = cartaElegida.getReverso()->getColor().getColorCarta();

    ResultadoJugada resultadoTirada;

    if(cartaElegida.getReverso()->getJerarquia() <9 ){

        resultadoTirada.darMensaje = true;
        resultadoTirada.tiempoMensaje = 1500;
        resultadoTirada.mensajeJugador = std::string("Se ha tirado la carta ") + cartaElegida.getReverso()->getNombre();

        this->pilaCentralCartas->push(cartaElegida);
        this->listaJugadores.getActual()->getMazo()->eliminar(indice);
        resultadoTirada.tiempoAnimacion = 2000;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.colorAviso = "#0C7527";
        return resultadoTirada;
    }

    if(cartaElegida.getReverso()->getTipo() == TipoCarta::CAMBIARDIRECCION && cartaElegida.getReverso()->getJerarquia() == 11){

        resultadoTirada.darMensaje = true;
        resultadoTirada.tiempoMensaje = 3000;

        resultadoTirada.mensajeJugador = std::string("El ")+ this->listaJugadores.getActual()->getNombre() + std::string(" tiro la carta ") + cartaElegida.getReverso()->getNombre() ;

        cartaElegida.getReverso()->lanzarCarta(*this,this->listaJugadores);
        this->pilaCentralCartas->push(cartaElegida);
        this->listaJugadores.getActual()->getMazo()->eliminar(indice);
        this->setPuedeMoverse(false);

        resultadoTirada.tiempoAnimacion = 2000;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.colorAviso = "#0C7527";

        return resultadoTirada;
    }


    resultadoTirada.jugadaValida = false;
    return resultadoTirada;

}


//Metodo que verifica si la carta tirada pertenece al mismo color (en claro)
bool Partida::esMismaClara(const Carta& cartaJugador, const Carta& cartaPila){

    if(cartaJugador.getAnverso()->getColor().getColorCarta() ==
        cartaPila.getAnverso()->getColor().getColorCarta()){
        return true;
    }

    // Coincide jerarquia
    if(cartaJugador.getAnverso()->getJerarquia() ==
        cartaPila.getAnverso()->getJerarquia()){
        return true;
    }

    return false;
}


//Metodo que verifica si la carta tirada pertenece al mismo color (en oscuro)
bool Partida::esMismaOscura(const Carta& cartaJugador, const Carta& cartaPila){

    // Coincide color
    if(cartaJugador.getReverso()->getColor().getColorCarta() ==
        cartaPila.getReverso()->getColor().getColorCarta()){
        return true;
    }

    // Coincide jerarquia
    if(cartaJugador.getReverso()->getJerarquia() ==
        cartaPila.getReverso()->getJerarquia()){
        return true;
    }

    return false;
}


//Metodo que le permite saber al programa si el usuario tiene la carta con el color necesario
bool Partida::tieneCartaNecesaria(){

    if(!this->estaFlip){
        return tieneEnClaras();
    }else{
        return tieneEnOscuras();
    }
}

//Metodo que permite verificar si tiene las cartas claras
bool Partida::tieneEnClaras(){

    Carta cartaCentral = this->pilaCentralCartas->verTop();
    ListaEnlazada<Carta>* mazo = this->listaJugadores.getActual()->getMazo();

    int cantidad = mazo->getLongitud();

    for(int i = 0; i < cantidad; i++){

        Carta cartaJugador = mazo->verValor(i);

        // Coincide color
        if(cartaJugador.getAnverso()->getColor().getColorCarta() ==
            cartaCentral.getAnverso()->getColor().getColorCarta()){
            return true;
        }

        // Coincide jerarquia
        if(cartaJugador.getAnverso()->getJerarquia() ==
            cartaCentral.getAnverso()->getJerarquia()){
            return true;
        }

        // Es comodin o carta especial
        if(cartaJugador.getAnverso()->getJerarquia() >13 ){
            return true;
        }
    }

    return false;
}

//Metodo que permite verificar si tiene las cartas oscuras
bool Partida::tieneEnOscuras(){

    if(!this->estaFlip){
        return false;
    }

    Carta cartaCentral = this->pilaCentralCartas->verTop();
    ListaEnlazada<Carta>* mazo = this->listaJugadores.getActual()->getMazo();

    int cantidad = mazo->getLongitud();

    for(int i = 0; i < cantidad; i++){

        Carta cartaJugador = mazo->verValor(i);

        // Coincide color
        if(cartaJugador.getReverso()->getColor().getColorCarta() ==
            cartaCentral.getReverso()->getColor().getColorCarta()){
            return true;
        }

        // Coincide jerarquia
        if(cartaJugador.getReverso()->getJerarquia() ==
            cartaCentral.getReverso()->getJerarquia()){
            return true;
        }

        // Es comodin o carta especial
        if(cartaJugador.getReverso()->getJerarquia() >13 ){
            return true;
        }
    }

    return false;
}


//Metodo que permite ejecutar la tirada
void Partida::ejecutarMovimiento(){

    if(this->direccion == "Derecha" && puedeMoverse){
        this->listaJugadores.avanzar();
        this->verificarVuelta();
    }
    else if(this->direccion == "Izquierda" && puedeMoverse){
        this->listaJugadores.retroceder();
        this->verificarVuelta();
    }
}

//Metodo que permite verificar si ya se ha dado una vuelta
void Partida::verificarVuelta(){
    if(this->inicioRonda.getDato() == this->listaJugadores.getActual()){
        this->cantidadVueltas++;
    }
}

//====================SUBREGION Metodos getter y setter=================
bool Partida::getPuedeMoverse(){
    return this->puedeMoverse;
}

void Partida::setPuedeMoverse(bool accion){
    this->puedeMoverse = accion;
}

bool Partida::getEstaFlip(){
    return this->estaFlip;
}

void Partida::setEstaFlip(bool accion){
    this->estaFlip = accion;
}

//====================Fin de la SUBREGION Metodos getter y setter=================

//==============FIN DEL APARTADO DE METODOS QUE PERMITEN RESPONDER A LAS ACCIONES DEL JUGADOR===================


//==============APARTADO DE METODOS GETTER DE LA CLASE===================

int Partida::getCantidadPila(){
    return this->pilaLateralCartas->getLongitud();
}
int Partida::getCantidadVueltas(){
    return this->cantidadVueltas;
}

std::string Partida::getDireccion(){
    return this->direccion;
}

//Retorna la pila central
std::string  Partida::imagenPilaCentral(){

    if(!this->estaFlip){
        return this->pilaCentralCartas->verTop().getAnverso()->getPathImagen();
    }else{
        return this->pilaCentralCartas->verTop().getReverso()->getPathImagen();
    }
}

//Retorna la pila lateral
std::string  Partida::imagenPilaLateral(){

    if(!this->estaFlip){
        return this->pilaCentralCartas->verTop().getAnverso()->getReversoModelo();
    }else{
        return this->pilaCentralCartas->verTop().getReverso()->getPathImagen();
    }
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

    for (int i = 0; i < 10; i++) {
        this->modelosClaros[i] = new Numerica(ColorCarta(TipoColor::ROJO),arregloNombres[j],"claro",j,j);
        j++;
    }

    j = 0;
    //Inicializacion de cartas numericas amarillas
    for (int i = 10; i < 20; i++) {
        this->modelosClaros[i] = new Numerica(ColorCarta(TipoColor::AMARILLO),arregloNombres[j],"claro",j,j);
        j++;
    }

    j = 0;
    //Inicializacion de cartas numericas verdes
    for (int i = 20; i < 30; i++) {
        this->modelosClaros[i] = new Numerica(ColorCarta(TipoColor::VERDE),arregloNombres[j],"claro",j,j);
        j++;
    }
    j = 0;
    //Inicializacion de cartas numericas azules
    for (int i = 30; i < 40; i++) {
        this->modelosClaros[i] = new Numerica(ColorCarta(TipoColor::AZUL),arregloNombres[j],"claro",j,j);
        j++;
    }

    //=======FIN INICIALIZACION CARTAS NUMERICAS=====

    //Generacion de cartas de sumar cantidad
    if(!this->configuracion.esFlip()){
        this->modelosClaros[40] = new SumaCantidad(ColorCarta(TipoColor::AZUL),"Mas dos Azul","claro",12,2);
        this->modelosClaros[41] = new SumaCantidad(ColorCarta(TipoColor::AMARILLO),"Mas dos Amarillo","claro",12,2);
        this->modelosClaros[42] = new SumaCantidad(ColorCarta(TipoColor::ROJO),"Mas dos Rojo","claro",12,2);
        this->modelosClaros[43] = new SumaCantidad(ColorCarta(TipoColor::VERDE),"Mas dos Verde","claro",12,2);
    }else{
        this->modelosClaros[40] = new SumaCantidad(ColorCarta(TipoColor::AZUL),"Mas uno Azul","claro",12,1);
        this->modelosClaros[41] = new SumaCantidad(ColorCarta(TipoColor::AMARILLO),"Mas uno Amarillo","claro",12,1);
        this->modelosClaros[42] = new SumaCantidad(ColorCarta(TipoColor::ROJO),"Mas uno Rojo","claro",12,1);
        this->modelosClaros[43] = new SumaCantidad(ColorCarta(TipoColor::VERDE),"Mas uno Verde","claro",12,1);
    }

    //Generacion de cartas de cambio de direccion
    this->modelosClaros[44] = new CambioDireccion(ColorCarta(TipoColor::AZUL),"Cambio direccion Azul","claro",11);
    this->modelosClaros[45] = new CambioDireccion(ColorCarta(TipoColor::AMARILLO),"Cambio direccion Amarillo","claro",11);
    this->modelosClaros[46] = new CambioDireccion(ColorCarta(TipoColor::ROJO),"Cambio direccion Rojo","claro",11);
    this->modelosClaros[47] = new CambioDireccion(ColorCarta(TipoColor::VERDE),"Cambio direccion Verde","claro",11);

    //Generacion de cartas de bloqueo
    this->modelosClaros[48] = new Bloqueo(ColorCarta(TipoColor::AZUL),"Bloqueo Azul","claro",10);
    this->modelosClaros[49] = new Bloqueo(ColorCarta(TipoColor::AMARILLO),"Bloqueo Amarillo","claro",10);
    this->modelosClaros[50] = new Bloqueo(ColorCarta(TipoColor::ROJO),"Bloqueo Rojo","claro",10);
    this->modelosClaros[51] = new Bloqueo(ColorCarta(TipoColor::VERDE),"Bloqueo Verde","claro",10);

    //Generacion de cartas multicolor comodin suma
    if(!this->configuracion.esFlip()){
        this->modelosClaros[52] = new MultiColorSuma(ColorCarta(TipoColor::MULTICOLOR),"Multicolor mas 4","claro",13,4);
    }else{
        this->modelosClaros[52] = new MultiColorSuma(ColorCarta(TipoColor::MULTICOLOR),"Multicolor mas 2","claro",13,2);
    }

    //Generacion de la carta comodin
    this->modelosClaros[53] = new ComodinColor(ColorCarta(TipoColor::MULTICOLOR),"Comodin","claro",14);

    //Carta ECLIPSE MIA (P)
    this->modelosClaros[54] = new Eclipse(ColorCarta(TipoColor::PREDETERMINADO),"Eclipse","claro",15);

    //Carta ESPIA MIA (P)
    this->modelosClaros[55] = new Espia(ColorCarta(TipoColor::PREDETERMINADO),"Espia","claro",16);

}

//Metodo que permite generar las cartas negras cuando se requieren
void Partida::generarCartasOscuras(){

    if(!this->configuracion.esFlip()){
        return;
    }

    std::string arregloNombres [] = {"cero","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"};

    int j = 0;
    //=======INICIALIZACION CARTAS NUMERICAS=====
    //Inicializacion de cartas numericas rosas

    for (int i = 0; i < 10; i++) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::ROSA),arregloNombres[j],"oscuro",j,j);
        j++;
    }

    j = 0;
    //Inicializacion de cartas numericas naranjas
    for (int i = 10; i < 20; i++) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::NARANJA),arregloNombres[j],"oscuro",j,j);
    }

    j = 0;
    //Inicializacion de cartas numericas turquesas
    for (int i = 20; i < 30; i++) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::TURQUESA),arregloNombres[j],"oscuro",j,j);
    }
    j = 0;
    //Inicializacion de cartas numericas violetas
    for (int i = 30; i < 40; i++) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::VIOLETA),arregloNombres[j],"oscuro",j,j);
    }

    //=======FIN INICIALIZACION CARTAS NUMERICAS=====


    //Generacion de las cartas oscuras +3
    this->modelosOscuros[40] = new SumaCantidad(ColorCarta(TipoColor::ROSA),"Mas tres Rosa","oscuro",12,3);
    this->modelosOscuros[41] = new SumaCantidad(ColorCarta(TipoColor::NARANJA),"Mas tres Naranja","oscuro",12,3);
    this->modelosOscuros[42] = new SumaCantidad(ColorCarta(TipoColor::VIOLETA),"Mas tres Violeta","oscuro",12,3);
    this->modelosOscuros[43] = new SumaCantidad(ColorCarta(TipoColor::TURQUESA),"Mas tres Turquesa","oscuro",12,3);

    //Generacion de cartas de cambio de direccion
    this->modelosOscuros[44] = new CambioDireccion(ColorCarta(TipoColor::ROSA),"Cambio direccion Rosa","oscuro",11);
    this->modelosOscuros[45] = new CambioDireccion(ColorCarta(TipoColor::NARANJA),"Cambio direccion Naranja","oscuro",11);
    this->modelosOscuros[46] = new CambioDireccion(ColorCarta(TipoColor::VIOLETA),"Cambio direccion Violeta","oscuro",11);
    this->modelosOscuros[47] = new CambioDireccion(ColorCarta(TipoColor::TURQUESA),"Cambio direccion Turquesa","oscuro",11);

    //Modelo de salto a todos
    this->modelosOscuros[48] = new SaltoTodos(ColorCarta(TipoColor::ROSA),"Salto Todos Rosa","oscuro",10);
    this->modelosOscuros[49] = new SaltoTodos(ColorCarta(TipoColor::NARANJA),"Salto Todos Naranja","oscuro",10);
    this->modelosOscuros[50] = new SaltoTodos(ColorCarta(TipoColor::VIOLETA),"Salto Todos Violeta","oscuro",10);
    this->modelosOscuros[51] = new SaltoTodos(ColorCarta(TipoColor::TURQUESA),"Salto Todos Turquesa","oscuro",10);

    //Modelo de comodin +6
    this->modelosOscuros[52] = new MultiColorSuma(ColorCarta(TipoColor::MULTICOLOR),"Multicolor mas 6","oscuro",13,6);

    //Modelo de comodin Color eterno
    this->modelosOscuros[53] = new ColorEterno(ColorCarta(TipoColor::PREDETERMINADO),"Color Eterno","oscuro",14);

    //Carta ECLIPSE MIA (P)
    this->modelosOscuros[54] = new Eclipse(ColorCarta(TipoColor::PREDETERMINADO),"Eclipse","oscuro",15);

    //Carta ESPIA MIA (P)
    this->modelosOscuros[55] = new Espia(ColorCarta(TipoColor::PREDETERMINADO),"Espia","oscuro",16);

}

//---------------------SUBREGION DE METODOS QUE GENERAN LA LISTA INICIAL DE CARTAS PARA PODERLAS REVOLVER-------------

//Metodo delegado para hacer todo lo requerido con las cartas
void Partida::armarCartas(){

    this->listadoCartas = new ListaEnlazada<Carta>();

    int cantidadMazos = ((this->cantidadJugadores-1)/6+1);

    qDebug()<<"CANTIDAD DE MAZOS: "<<cantidadMazos;

    for (int i = 0; i < cantidadMazos; i++) {
        if(!this->configuracion.esFlip()){
            armarCartasNormal(this->listadoCartas);
        }else{
            armarCartasFlip(this->listadoCartas);
        }
    }


    barajarCartas(this->listadoCartas);

    //Se agrega todo a la pila lateral de cartas
    this->pilaLateralCartas = new Pila<Carta>();

    while (this->listadoCartas->getLongitud() > 0) {
        pilaLateralCartas->push(
            listadoCartas->popFront()
            );
    }

    delete this->listadoCartas;
    this->listadoCartas = nullptr;

    this->pilaCentralCartas = new Pila<Carta>();
}

//Metodo que permite armar las cartas del UNO Normal
void Partida::armarCartasNormal(ListaEnlazada<Carta>*& lista){

    int modeloIndex = 0;

    //Generacion de cartas numericas
    for (int i = 0; i < 40; i++) {

        lista->insertarFrente(Carta(nullptr, this->modelosClaros[i], modeloIndex));

        modeloIndex++;
        if(modeloIndex >= 10){
            modeloIndex = 0;
        }
    }

    int j = 0;

    modeloIndex = 1;

    do {
        //Evita enumerar el cero
        if (j % 10 != 0) {
            lista->insertarFrente(Carta(nullptr, this->modelosClaros[j], modeloIndex));
            modeloIndex++;
        }

        if (modeloIndex >= 10) {
            modeloIndex = 1;
        }

        j++;
    } while (j < 40);

    //Generacion de las cartas +2
    for (int i = 0; i < 2; i++) {
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[40], 12));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[41], 12));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[42], 12));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[43], 12));
    }

    //Generacion de las cartas cambio de direccion
    for (int i = 0; i < 2; i++) {
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[44], 11));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[45], 11));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[46], 11));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[47], 11));
    }

    //Generacion de las cartas cambio de bloqueo
    for (int i = 0; i < 2; i++) {
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[48], 10));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[49], 10));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[50], 10));
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[51], 10));
    }

    //Generar carta multicolor suma
    for (int i = 0; i < 4; i++) {
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[52], 13));
    }

    //Generar Carta comodin color
    for (int i = 0; i < 4; i++) {
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[53], 14));
    }

    //Generar carta eclipse MIA (P)
    for (int i = 0; i < 4; i++) {
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[54], 15));
    }

    //Generar carta espia MIA (P)
    for (int i = 0; i < 4; i++) {
        lista->insertarFrente(Carta(nullptr, this->modelosClaros[55], 16));
    }
}

//Metodo que permite armar las cartas del UNO FLIP
void Partida::armarCartasFlip(ListaEnlazada<Carta>*& lista){

    if(!this->configuracion.esFlip()) return;

    this->listaCartasBlancas= new ListaEnlazada<Carta>();
    this->armarCartasNormal(this->listaCartasBlancas);

    this->listadoCartasOscuras = new ListaEnlazada<Carta>();
    this->armarCartasOscuras(this->listadoCartasOscuras);

    barajarCartas(this->listaCartasBlancas);
    barajarCartas(this->listadoCartasOscuras);

    int cantidadCartas =this->listadoCartasOscuras->getLongitud();

    for (int i = 0; i < cantidadCartas; i++) {

        Modelo* clara = this->listaCartasBlancas->popFront().getAnverso();
        Modelo* oscura = this->listadoCartasOscuras->popFront().getReverso();

        this->listadoCartas->insertarFrente(Carta(oscura, clara, i));
    }

    //SE LIBERA LA MEMORIA OCUPADA
    delete this->listaCartasBlancas;
    delete this->listadoCartasOscuras;
    this->listadoCartasOscuras = nullptr;
    this->listaCartasBlancas = nullptr;

}

//METODO QUE SIRVE PARA REPARTIR LAS REFERENCIAS DE LAS CARTAS OSCURAS
void Partida::armarCartasOscuras(ListaEnlazada<Carta>*& lista){

    if(!this->configuracion.esFlip()) return;

    int modeloIndex = 0;

    //Generacion de cartas numericas
    for (int i = 0; i < 40; i++) {

        lista->insertarFrente(Carta(this->modelosOscuros[i],nullptr, modeloIndex));
        modeloIndex++;
        if(modeloIndex >= 10){
            modeloIndex = 0;
        }
    }

    int j = 0;

    modeloIndex = 1;

    do {
        //Evita enumerar el cero
        if (j % 10 != 0) {
            lista->insertarFrente(Carta(this->modelosOscuros[j],nullptr, modeloIndex));
            modeloIndex++;
        }

        if (modeloIndex >= 10) {
            modeloIndex = 1;
        }

        j++;
    } while (j < 40);


    //Generacion de las cartas +2
    for (int i = 0; i < 2; i++) {
        lista->insertarFrente(Carta( this->modelosOscuros[40],nullptr, 12));
        lista->insertarFrente(Carta( this->modelosOscuros[41], nullptr,12));
        lista->insertarFrente(Carta(this->modelosOscuros[42], nullptr, 12));
        lista->insertarFrente(Carta( this->modelosOscuros[43], nullptr,12));
    }


    //Generacion de las cartas cambio de direccion
    for (int i = 0; i < 2; i++) {
        lista->insertarFrente(Carta( this->modelosOscuros[44],nullptr, 11));
        lista->insertarFrente(Carta(this->modelosOscuros[45], nullptr,11));
        lista->insertarFrente(Carta( this->modelosOscuros[46],nullptr, 11));
        lista->insertarFrente(Carta(this->modelosOscuros[47],nullptr, 11));
    }

    //Generacion de las cartas cambio de salto total
    for (int i = 0; i < 2; i++) {
        lista->insertarFrente(Carta( this->modelosOscuros[48],nullptr, 10));
        lista->insertarFrente(Carta( this->modelosOscuros[49],nullptr, 10));
        lista->insertarFrente(Carta( this->modelosOscuros[50],nullptr, 10));
        lista->insertarFrente(Carta( this->modelosOscuros[51],nullptr, 10));
    }

    //Generar carta multicolor suma
    for (int i = 0; i < 4; i++) {
        lista->insertarFrente(Carta( this->modelosOscuros[52],nullptr, 13));
    }

    //Cartas comodin color eterno
    for (int i = 0; i < 4; i++) {
        lista->insertarFrente(Carta( this->modelosOscuros[53],nullptr, 14));
    }

    //Generar carta eclipse MIA (P)
    for (int i = 0; i < 4; i++) {
        lista->insertarFrente(Carta( this->modelosOscuros[54],nullptr, 15));
    }

    //Generar carta espia MIA (P)
    for (int i = 0; i < 4; i++) {
        lista->insertarFrente(Carta( this->modelosOscuros[55],nullptr, 16));
    }

}

//Metodos que sirven para poder barajear y mezclar las cartas (DE LOS MAS IMPORTANTES)
void Partida::barajarCartas(ListaEnlazada<Carta>*& lista){

    if (!lista) return;

    int n = lista->getLongitud();
    if (n <= 1) return;

    //Se inicializa la semilla una zola vez
    static bool semillaInicializada = false;
    if (!semillaInicializada) {
        std::srand(std::time(nullptr));
        semillaInicializada = true;
    }

    //Arreglo estatico con el maximo tamanio posible
    Carta* buffer = new Carta[n];

    //Copiar la lista tal cual al arreglo (basandose en puro recorrido de getsiguiente)
    Nodo<Carta>* actual = lista->getCabeza();
    int i = 0;

    while (actual != nullptr && i < n) {
        buffer[i] = actual->getDato();
        actual = actual->getSiguiente();
        i++;
    }

    //Metodo Fisher–Yates manual algoritmo base para poder barajar de forma uniforme
    for (int i = n - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);


        Carta temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    //Se reescriben los datos en la lista
    actual = lista->getCabeza();
    i = 0;

    while (actual != nullptr && i < n) {
        actual->getDato() = buffer[i];
        actual = actual->getSiguiente();
        i++;
    }
    delete[] buffer;
}

//---------------------FIN DE LA SUBREGION DE METODOS QUE GENERAN LA LISTA INICIAL DE CARTAS PARA PODERLAS REVOLVER-------------

//==============FIN DEL APARTADO DE METODOS DE GENERACION DE CARTAS DEL JUEGO===================

//Metodo para limpiar las cosas en el destructor
void Partida::limpiarReferencias(){
    for(int i = 0; i < 56; i++)
        delete modelosClaros[i];

    if(this->configuracion.esFlip()){
        for(int i = 0; i < 56; i++)
            delete modelosOscuros[i];
    }

    delete this->pilaCentralCartas;
    delete this->pilaLateralCartas;
}

Partida::~Partida(){
    limpiarReferencias();
}

//CREATED BY (P.M)

