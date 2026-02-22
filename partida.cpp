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
#include "reversa.h"
#include "saltotodos.h"
#include "sumacantidad.h"
#include <QRandomGenerator>

/*CREATED BY PABLO M*/

Partida::Partida(int _cantidadJugadores,DatosConfiguracion* &config)
    :cantidadJugadores(_cantidadJugadores),listaJugadores(), configuracion(config), direccion("Derecha"), cantidadVueltas(0), estaFlip(false), puedeMoverse(true),colorPartida("PREDETERMINADO"),vecesSumadasCarta(0), puedeRetar(false), estaEclpse(false)

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
    ejecutarPrimerMovimiento();
    definirColorPrincipal();

}


//Metodo que permite setear el color actual de la partida (MUY UTIL PARA LAS CARTAS ESPECIALES)
void Partida::establecerColorPartida(TipoColor colorCarta){
//(P)
    switch (colorCarta) {
    case TipoColor::AMARILLO:
        this->colorPartida = "AMARILLO";
        return;
    case TipoColor::VERDE:
        this->colorPartida = "VERDE";
        return;
    case TipoColor::ROJO:
        this->colorPartida = "ROJO";
        return;
    case TipoColor::AZUL:
        this->colorPartida = "AZUL";
        return;
    case TipoColor::NARANJA:
        this->colorPartida = "NARANJA";
        return;
    case TipoColor::ROSA:
        this->colorPartida = "ROSA";
        return;
    case TipoColor::VIOLETA:
        this->colorPartida = "VIOLETA";
        return;
    case TipoColor::TURQUESA:
        this->colorPartida = "TURQUESA";
        return;

    default:
        this->colorPartida = "ROJO";
        return;
    }

}

//Metodo que permite generar un color de la partida aleatorio si en dado caso toca una carta multicolor
void Partida:: definirColorPrincipal(){
    //(P)
    if(this->pilaCentralCartas->estaVacia()){
        return;
    }

    Carta cartaPrincipal = this->pilaCentralCartas->verTop();

    Modelo * modeloCarta = nullptr;

    if(this->estaFlip){
        modeloCarta = cartaPrincipal.getReverso();
    }else{
        modeloCarta = cartaPrincipal.getAnverso();
    }

    if(modeloCarta->getJerarquia()< 13){
        this->establecerColorPartida(modeloCarta->getColor().getColorCarta());
        return;
    }

    TipoColor colorAleatorio = generarColorAleatorio();
    this->establecerColorPartida(colorAleatorio);

}

//Metodo que permite obtener un color aleatorio cuando sale una carta especial
TipoColor Partida::generarColorAleatorio() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 4);

    int num = dis(gen);

    if (!this->estaFlip) {
        switch(num) {
        case 1: return TipoColor::AMARILLO;
        case 2: return TipoColor::VERDE;
        case 3: return TipoColor::ROJO;
        default: return TipoColor::AZUL;
        }
    } else {
        switch(num) {
        case 1: return TipoColor::NARANJA;
        case 2: return TipoColor::ROSA;
        case 3: return TipoColor::VIOLETA;
        default: return TipoColor::TURQUESA;
        }
    }
}

//Metodo que permite retornar el color en base a la decision tomada
TipoColor Partida::getColorDecision(int decision) {

    if (this->estaFlip) {

        switch(decision) {
        case 1: return TipoColor::NARANJA;
        case 2: return TipoColor::ROSA;
        case 3: return TipoColor::VIOLETA;
        default: return TipoColor::TURQUESA;
        }
    } else {
        switch(decision) {
        case 1: return TipoColor::AMARILLO;
        case 2: return TipoColor::VERDE;
        case 3: return TipoColor::ROJO;
        default: return TipoColor::AZUL;
        }
    }
}

//Metodo que retorna el color de la partida
TipoColor Partida::getColorPartida(){

    if (this->colorPartida == "AMARILLO") {
        return TipoColor::AMARILLO;
    }
    else if(this->colorPartida == "VERDE"){
        return TipoColor::VERDE;
    }
    else if(this->colorPartida == "ROJO"){
        return TipoColor::ROJO;
    }
    else if(this->colorPartida == "AZUL"){
        return TipoColor::AZUL;
    }
    else if(this->colorPartida == "NARANJA"){
        return TipoColor::NARANJA;
    }
    else if(this->colorPartida == "ROSA"){
        return TipoColor::ROSA;
    }
    else if(this->colorPartida == "VIOLETA"){
        return TipoColor::VIOLETA;
    }
    else if(this->colorPartida == "TURQUESA"){
        return TipoColor::TURQUESA;
    }
    else{
        return TipoColor::PREDETERMINADO;
    }
}

/*===============APARTADO DE METODOS QUE PERMITEN VALIDAR EL JUGADOR EN UNO===============*/
std::string Partida::gritarUno(std::string texto){

    for (int i = 0; i < texto.length(); i++) {
        texto[i] = std::tolower(texto[i]);
    }

    if (texto != "uno") {
        throw std::runtime_error("¡DEBES ESCRIBIR LA PALABRA \" UNO \"!");
    }

    bool dijoAnteriorUno = this->pickJugadorAnterior()->getDijoUno();


    if(this->getJugadorActual()->estaPropensoUno()){
        this->getJugadorActual()->setDijoUno(true);
        return std::string("¡EL JUGADOR ")+ this->getJugadorActual()->getNombre() +std::string(" HA GRITADO \" UNO \"!");
    }
    else if (!dijoAnteriorUno){
        //Penalizacion al jugador que no dijo UNO
        Jugador * jugadorAnteriorGrito = this->pickJugadorAnterior();
        this->penalizarJugador(jugadorAnteriorGrito);
        return std::string("¡EL ")+ this->pickJugadorAnterior()->getNombre() +std::string(" HA SIDO PENALIZADO +2 CARTAS");

    }else if(dijoAnteriorUno){
        //Penalizacion al jugador que quizo penalizar al anterior
        Jugador * jugadoActualGrito = this->getJugadorActual();
        this->penalizarJugador(jugadoActualGrito);
        return std::string("¡HAS SIDO PENALIZADO EL ")+ this->pickJugadorAnterior()->getNombre() +std::string(" YA GRITO \" UNO \"!");
    }

    throw std::runtime_error("¡NO SE EJECUTO LA ACCION DE GRITO \" UNO \"!");
}

//Metodo que permite penalizar al jugador acorde a la accion determinada( METODO COMPLEMENTARIO)
void Partida::penalizarJugador(Jugador * &jugadorParam){

    Pila<Carta> * pilaLateral = this->getPilaLateral();

    for (int i = 0; i < 2; i++) {
        if (pilaLateral->estaVacia()) {
            this->llenarPilaLateral();
        }

        if (pilaLateral->estaVacia()) break;

        Carta cartaDesapilada = pilaLateral->verTop();
        jugadorParam->getMazo()->insertarFrente(cartaDesapilada);
        pilaLateral->pop();
    }

    jugadorParam->ordenarCartas(this->estaFlip);
}

/*===============FIN DEL APARTADO DE METODOS QUE PERMITEN VALIDAR EL JUGADOR EN UNO===============*/

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
}

//Metodo que saca la primera carta
void Partida::ejecutarPrimerMovimiento(){
    //Saca la primera carta
    Carta cartaInicial = this->pilaLateralCartas->verTop();
    this->pilaCentralCartas->push(cartaInicial);
    this->pilaLateralCartas->pop();

}

//Metodo que avisa a cada jugador que desordene sus propias cartas (METODO DE CARTA ECLIPSE)
void Partida::desordenarCartas(){
    int totalJugadores = this->listaJugadores.getLongitud();
    for (int i = 0; i < totalJugadores; i++) {
        this->listaJugadores.getActual()->desordenarCartas();
        this->listaJugadores.avanzar();
    }
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

//Metodo que le permite al usuario tomar carta
ResultadoJugada Partida::tomarCarta(){

    ResultadoJugada resultado;

    try{

        Carta cartaTomada = this->pilaLateralCartas->verTop();

        this->listaJugadores.getActual()->getMazo()->insertarFrente(cartaTomada);
        this->pilaLateralCartas->pop();
        this->listaJugadores.getActual()->ordenarCartas(this->estaFlip);

        resultado.analizarStack = true;

        if(this->getJugadorActual()->getObligadoSacar()){
            this->evaluarObligacionColor(resultado, cartaTomada);
            return resultado;
        }

        if(this->configuracion.esModoRobo()){
            resultado.jugadaValida = true;
            return resultado;
        }

        resultado.tiempoAnimacion = 2500;
        resultado.tiempoMensaje = 2000;
        resultado.darMensaje = true;
        resultado.colorAviso = "#91042B";
        resultado.jugadaValida = false;
        resultado.mensajeJugador = "Modo robo desactivado. Solo puedes sacar una";
        return resultado;

    }catch(const std::runtime_error & ex){
        resultado.jugadaValida = false;
        return resultado;
    }
}


//Metodo auxiliar que permite saber que se va a determinar cuando el jugador esta obligado a sacar una carta
void Partida::evaluarObligacionColor(ResultadoJugada &resultado, Carta &cartaTomada){

    TipoColor colorObligado = this->getJugadorActual()->getColorObligado();
    resultado.tiempoAnimacion = 2500;
    resultado.tiempoMensaje = 2000;
    resultado.darMensaje = true;
    resultado.jugadaValida = true;

    Jugador * jugadorActual = this->getJugadorActual();


    if(!this->estaFlip){
        if(cartaTomada.getAnverso()->getColor() == colorObligado){
            jugadorActual->setObligadoSacar(false);
            jugadorActual->setColorObligado(TipoColor::PREDETERMINADO);
            resultado.colorAviso = "#0C7527";
            resultado.mensajeJugador = "Saliste del efecto de Color Eterno";

            return;
        }else{
            std::string mensajeColor = this->getJugadorActual()->saberColorObligado(colorObligado);
            resultado.colorAviso = "#91042B";
            resultado.mensajeJugador = "ESTAS OBLIGADO A SACAR UNA CARTA DE COLOR " + mensajeColor;
            return;
        }
    }else{
        if(cartaTomada.getReverso()->getColor() == colorObligado){
            jugadorActual->setObligadoSacar(false);
            jugadorActual->setColorObligado(TipoColor::PREDETERMINADO);
            resultado.colorAviso = "#0C7527";
            resultado.mensajeJugador = "Saliste del efecto de Color Eterno";

            return;
        }else{
            std::string mensajeColor = this->getJugadorActual()->saberColorObligado(colorObligado);
            resultado.colorAviso = "#91042B";
            resultado.mensajeJugador = "ESTAS OBLIGADO A SACAR UNA CARTA DE COLOR " + mensajeColor;
            return;
        }
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

    //Condicion que hace efecto solo si el jugador esta obligado a sacar un color
    if(this->getJugadorActual()->getObligadoSacar()){
        TipoColor colorObligado = this->getJugadorActual()->getColorObligado();
        std::string mensajeColor = this->getJugadorActual()->saberColorObligado(colorObligado);

        throw std::runtime_error(std::string( "ESTAS OBLIGADO A SACAR UNA CARTA COLOR: ") + mensajeColor);
    }

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

    if(this->getJugadorActual()->getEstaObligado()){

        Carta cartaActual = this->listaJugadores.getActual()->getMazo()->getValor(indice);

        if(this->estaFlip){

            if(cartaActual.getReverso()->getTipo() != this->getJugadorActual()->getTipoObligado()){
                Modelo * modeloCarta = this->pilaStacking->verTop().getReverso();
                throw std::runtime_error(std::string( "Obligado a tirar similar a ") + modeloCarta->getNombre());
            }

        }else{

            if(cartaActual.getAnverso()->getTipo() != this->getJugadorActual()->getTipoObligado()){
                Modelo * modeloCarta = this->pilaStacking->verTop().getAnverso();
                throw std::runtime_error(std::string( "Obligado a tirar similar a ") + modeloCarta->getNombre());
            }
        }
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
            return this->accionCartaEspecialClara(indice);
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
            return this->accionCartaEspecialOscura(indice);
        }
    }

    throw std::runtime_error("No se pudo ejecutar la tirada");
}

//Metodo que permite ejecutar la decision del jugador ya que selecciono un color
ResultadoJugada Partida::ejecutarDecision(int indice, int decision){

    Carta cartaElegida = this->listaJugadores.getActual()->getMazo()->verValor(indice);
    ColorCarta color = cartaElegida.getAnverso()->getColor().getColorCarta();

    if(!this->estaFlip){

        //Opcion cuando se tira la carta comodin
        if(cartaElegida.getAnverso()->getTipo() == TipoCarta::COLORCOMODIN && cartaElegida.getAnverso()->getJerarquia() == 14){
            return this->tirarCartaComodinClara(cartaElegida,decision,indice);
        }
        //Opcion cuando se tira la multicolor clara
        if(cartaElegida.getAnverso()->getTipo() == TipoCarta::SUMAMULTICOLOR && cartaElegida.getAnverso()->getJerarquia() == 13){
            return this->tirarCartaSumaComodinClara(cartaElegida,decision,indice);
        }
    }else{

        //Opcion cuando se tira la multicolor oscura
        if(cartaElegida.getReverso()->getTipo() == TipoCarta::SUMAMULTICOLOR && cartaElegida.getReverso()->getJerarquia() == 13){
            return this->tirarCartaSumaComodinOscura(cartaElegida,decision,indice);
        }

        //Opcion cuando se tira LA CARTA COLOR ETERNO
        if(cartaElegida.getReverso()->getTipo() == TipoCarta::ETERNA && cartaElegida.getReverso()->getJerarquia() == 14){
            return this->tirarCartaEternaOscura(cartaElegida,decision,indice);
        }
    }
    ResultadoJugada resultadoTirada;
    resultadoTirada.colorAviso = "#91042B";
    resultadoTirada.jugadaValida = false;
    return resultadoTirada;

}

//============== APARTADO DE MIS CARTAS ESPECIALES CREADAS POR MI (P) ==============
//Tirado de mi carta eclipse
ResultadoJugada Partida::tirarCartaEclipse(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;

    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 2000;

    Modelo* modeloActivo;

    if(this->estaFlip){
        modeloActivo = cartaElegida.getReverso();
    }else{
        modeloActivo = cartaElegida.getAnverso();
    }

    resultadoTirada.mensajeJugador =
        std::string("HAS TIRADO LA CARTA ") + modeloActivo->getNombre();

    modeloActivo->lanzarCarta(*this);

    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);
    this->inicioRonda = this->listaJugadores.getActual();

    TipoColor colorAleatorio = generarColorAleatorio();
    this->establecerColorPartida(colorAleatorio);
    desordenarCartas();

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoAnimacion = 2500;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0A0909";
    resultadoTirada.analizarStack = true;

    return resultadoTirada;

}
//Tirado de mi carta espia
ResultadoJugada Partida::tirarCartaEspia(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;

    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 2500;

    Modelo* modeloActivo;

    if(this->estaFlip){
        modeloActivo = cartaElegida.getReverso();
    }else{
        modeloActivo = cartaElegida.getAnverso();
    }

    resultadoTirada.mensajeJugador =
        std::string("HAS TIRADO LA CARTA ") + modeloActivo->getNombre();

    modeloActivo->lanzarCarta(*this);

    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);
    TipoColor colorAleatorio = generarColorAleatorio();
    this->establecerColorPartida(colorAleatorio);
    this->setPuedeMoverse(false);

    resultadoTirada.requiereDecision = false;
    resultadoTirada.esEspia = true;
    resultadoTirada.tiempoAnimacion = 3000;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0A0909";
    resultadoTirada.analizarStack = true;

    return resultadoTirada;
}

//===================APARTADO DE METODOS DE TIRADO DE CARTAS ESPECIALES CLARAS =====================

//Metodo que permite setear el color acorde al parametro elegido por el usuario
void Partida::setColorJuegoSelect(ResultadoJugada &resultadoTirada, int decision){

    resultadoTirada.jugadaValida = true;

    if(!this->estaFlip){
        switch (decision) {
        case 1:
            resultadoTirada.mensajeJugador = std::string("SE DEBEN TIRAR CARTAS DE COLOR ROJO");
            this->establecerColorPartida(TipoColor::ROJO);
            return;
        case 2:
            resultadoTirada.mensajeJugador = std::string("SE DEBEN TIRAR CARTAS DE COLOR AZUL");
            this->establecerColorPartida(TipoColor::AZUL);
            return;
        case 3:
            resultadoTirada.mensajeJugador = std::string("SE DEBEN TIRAR CARTAS DE COLOR VERDE");
            this->establecerColorPartida(TipoColor::VERDE);
            return;
        case 4:
            resultadoTirada.mensajeJugador = std::string("SE DEBEN TIRAR CARTAS DE COLOR AMARILLO");
            this->establecerColorPartida(TipoColor::AMARILLO);
            return;
        default:
            resultadoTirada.mensajeJugador = std::string("NO SE ESTABLECIO NINGUN COLOR");
            resultadoTirada.colorAviso = "#91042B";
            resultadoTirada.jugadaValida = false;
            resultadoTirada.requiereDecision = false;
            return;
        }
    }else{
        switch (decision) {
        case 1:
            resultadoTirada.mensajeJugador = std::string("SE DEBEN TIRAR CARTAS DE COLOR NARANJA");
            this->establecerColorPartida(TipoColor::NARANJA);
            return;
        case 2:
            resultadoTirada.mensajeJugador = std::string("SE DEBEN TIRAR CARTAS DE COLOR VIOLETA");
            this->establecerColorPartida(TipoColor::VIOLETA);
            return;
        case 3:
            resultadoTirada.mensajeJugador = std::string("SE DEBEN TIRAR CARTAS DE COLOR TURQUESA");
            this->establecerColorPartida(TipoColor::TURQUESA);
            return;
        case 4:
            resultadoTirada.mensajeJugador = std::string("SE DEBEN TIRAR CARTAS DE COLOR ROSA");
            this->establecerColorPartida(TipoColor::ROSA);
            return;
        default:
            resultadoTirada.mensajeJugador = std::string("NO SE ESTABLECIO NINGUN COLOR");
            resultadoTirada.colorAviso = "#91042B";
            resultadoTirada.jugadaValida = false;
            resultadoTirada.requiereDecision = false;
            return;
        }
    }
}

//Claras
ResultadoJugada Partida::tirarCartaComodinClara(Carta& cartaElegida, int decision,int indice){
    ResultadoJugada resultadoTirada;
    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 2000;

    this->setColorJuegoSelect(resultadoTirada,decision);

    if(!resultadoTirada.jugadaValida){
        return resultadoTirada;
    }

    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);

    resultadoTirada.tiempoAnimacion = 2500;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.requiereDecision = false;
    resultadoTirada.analizarStack = true;

    return resultadoTirada;
}
ResultadoJugada Partida::tirarCartaSumaComodinClara(Carta& cartaElegida, int decision,int indice){
    ResultadoJugada resultadoTirada;

    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 2000;

    this->setColorJuegoSelect(resultadoTirada,decision);

    if(!resultadoTirada.jugadaValida){

        return resultadoTirada;
    }
//(P)
    resultadoTirada.mensajeJugador = std::string("Tiraste una carta ") + cartaElegida.getAnverso()->getNombre();

    this->pilaCentralCartas->push(cartaElegida);
    this->pilaStacking->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);

    if(this->getJugadorActual()->getEstaObligado()){
        this->getJugadorActual()->setEstaObligado(false);
        this->getJugadorActual()->setTipoObligado(TipoCarta::Predeterminado);
    }

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoAnimacion = 2500;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = false;

    return resultadoTirada;
}

//Oscuras
ResultadoJugada Partida::tirarCartaSumaComodinOscura(Carta& cartaElegida, int decision,int indice){

    ResultadoJugada resultadoTirada;

    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 2000;

    this->setColorJuegoSelect(resultadoTirada,decision);

    if(!resultadoTirada.jugadaValida){

        return resultadoTirada;
    }

    resultadoTirada.mensajeJugador = std::string("Tiraste una carta ") + cartaElegida.getReverso()->getNombre();

    this->pilaCentralCartas->push(cartaElegida);
    this->pilaStacking->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);

    if(this->getJugadorActual()->getEstaObligado()){
        this->getJugadorActual()->setEstaObligado(false);
        this->getJugadorActual()->setTipoObligado(TipoCarta::Predeterminado);
    }

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoAnimacion = 2500;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = false;

    return resultadoTirada;
}

ResultadoJugada Partida::tirarCartaEternaOscura(Carta& cartaElegida, int decision,int indice){

    ResultadoJugada resultadoTirada;

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoMensaje = 2000;
    resultadoTirada.tiempoAnimacion = 2500;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = true;

    resultadoTirada.darMensaje = true;
    cartaElegida.getReverso()->lanzarCarta(*this,this->listaJugadores);

    Jugador * jugadorSiguiente = this->pickJugadorSiguiente();
    TipoColor colorObligado = this->getColorDecision(decision);
    jugadorSiguiente->setColorObligado(colorObligado);

    resultadoTirada.mensajeJugador = std::string("Tiraste una carta ") + cartaElegida.getReverso()->getNombre();

    return resultadoTirada;
}


//===================FIN DEL APARTADO DE METODOS DE TIRADO DE CARTAS ESPECIALES CLARAS =====================

//Metodo que se utiiza para poder ejecutar la accion de una carta especial de jerarquia 13 para 16 CLARA
ResultadoJugada Partida::accionCartaEspecialClara(int indice){
    Carta cartaElegida = this->listaJugadores.getActual()->getMazo()->verValor(indice);

    ColorCarta color = cartaElegida.getAnverso()->getColor().getColorCarta();

    ResultadoJugada resultadoTirada;

    //Opcion cuando se tira una carta comodin
    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::COLORCOMODIN && cartaElegida.getAnverso()->getJerarquia() == 14){

        resultadoTirada.darMensaje = false;
        resultadoTirada.tiempoMensaje = 2000;
        resultadoTirada.mensajeJugador = std::string("Tiraste una carta ") + cartaElegida.getAnverso()->getNombre() ;
        resultadoTirada.requiereDecision = true;
        resultadoTirada.tiempoAnimacion = 3000;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.analizarStack = true;

        this->setPuedeMoverse(false);
        return resultadoTirada;
    }

    //Opcion cuando se tira una carta comodin que suma una cantidad
    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::SUMAMULTICOLOR && cartaElegida.getAnverso()->getJerarquia() == 13){

        resultadoTirada.darMensaje = true;
        resultadoTirada.tiempoMensaje = 2000;
        resultadoTirada.mensajeJugador = std::string("Tiraste una carta ") + cartaElegida.getAnverso()->getNombre() ;
        resultadoTirada.requiereDecision = true;
        resultadoTirada.tiempoAnimacion = 3000;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.colorAviso = "#0C7527";
        resultadoTirada.analizarStack = false;

        this->setPuedeMoverse(false);
        return resultadoTirada;
    }

    //Tiro de carta eclipse clara
    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::CARTAECLIPSE && cartaElegida.getAnverso()->getJerarquia() == 15){
        return this->tirarCartaEclipse(cartaElegida,indice);
    }

    //Tiro de carta espia clara (MIA)
    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::CARTAESPIA && cartaElegida.getAnverso()->getJerarquia() == 16){
        return this->tirarCartaEspia(cartaElegida,indice);
    }

    resultadoTirada.colorAviso = "#91042B";
    resultadoTirada.jugadaValida = false;
    return resultadoTirada;
}

//Metodo que se utiiza para poder ejecutar la accion de una carta especial de jerarquia 13 para 16 OSCURA
ResultadoJugada Partida::accionCartaEspecialOscura(int indice){

    Carta cartaElegida = this->listaJugadores.getActual()->getMazo()->verValor(indice);

    ColorCarta color = cartaElegida.getReverso()->getColor().getColorCarta();

    ResultadoJugada resultadoTirada;

    //Opcion cuando se tira LA CARTA COLOR ETERNO
    if(cartaElegida.getReverso()->getTipo() == TipoCarta::ETERNA && cartaElegida.getReverso()->getJerarquia() == 14){

        resultadoTirada.darMensaje = false;
        resultadoTirada.tiempoMensaje = 2000;
        resultadoTirada.requiereDecision = true;
        resultadoTirada.tiempoAnimacion = 2500;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.analizarStack = true;

        this->setPuedeMoverse(false);
        return resultadoTirada;
    }

    //Opcion cuando se tira una carta comodin que suma una cantidad
    if(cartaElegida.getReverso()->getTipo() == TipoCarta::SUMAMULTICOLOR && cartaElegida.getReverso()->getJerarquia() == 13){

        resultadoTirada.darMensaje = true;
        resultadoTirada.tiempoMensaje = 2000;
        resultadoTirada.mensajeJugador = std::string("Tiraste una carta ") + cartaElegida.getReverso()->getNombre();
        resultadoTirada.requiereDecision = true;
        resultadoTirada.tiempoAnimacion = 3500;
        resultadoTirada.jugadaValida = true;
        resultadoTirada.colorAviso = "#0C7527";
        resultadoTirada.analizarStack = false;

        this->setPuedeMoverse(false);
        return resultadoTirada;
    }

    //Tiro de carta eclipse oscura (MIA) (P)
    if(cartaElegida.getReverso()->getTipo() == TipoCarta::CARTAECLIPSE && cartaElegida.getReverso()->getJerarquia() == 15){
        return this->tirarCartaEclipse(cartaElegida,indice);
    }

    //Tiro de carta espia oscura (MIA) (P)
    if(cartaElegida.getReverso()->getTipo() == TipoCarta::CARTAESPIA && cartaElegida.getReverso()->getJerarquia() == 16){
        return this->tirarCartaEspia(cartaElegida,indice);
    }

    resultadoTirada.colorAviso = "#91042B";
    resultadoTirada.jugadaValida = false;
    return resultadoTirada;

}

//Metodo utilizado para ejecutar la accion de cada carta clara
ResultadoJugada Partida::ejecutarAccionCartaClara(int indice){

    Carta cartaElegida = this->listaJugadores.getActual()->getMazo()->verValor(indice);

    ColorCarta color = cartaElegida.getAnverso()->getColor().getColorCarta();

    Modelo * modeloPila = this->pilaCentralCartas->verTop().getAnverso();

    int jerarquia = cartaElegida.getAnverso()->getJerarquia();

    //Tiro de carta cambio de direccion de las cartas (reversa)
    if(jerarquia == -1 && this->configuracion.esFlip() && cartaElegida.getAnverso()->getTipo() == TipoCarta::REVERSE){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarCartaReversa(cartaElegida, indice,true);
        }

        if(cartaElegida.getAnverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarCartaReversa(cartaElegida, indice,true);
        }
    }

    if(jerarquia>= 0 &&  jerarquia<= 9){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarCartaNumericaClara(cartaElegida, indice);
        }

        if(cartaElegida.getAnverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarCartaNumericaClara(cartaElegida, indice);
        }
    }

    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::CARTABLOQUEO && jerarquia == 10 ){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarBloqueoClara(cartaElegida, indice);
        }

        if(cartaElegida.getAnverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarBloqueoClara(cartaElegida, indice);
        }
    }

    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::CAMBIARDIRECCION && jerarquia == 11){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarCambioDireccionClara(cartaElegida, indice);
        }

        if(cartaElegida.getAnverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarCambioDireccionClara(cartaElegida, indice);
        }
    }

    if(cartaElegida.getAnverso()->getTipo() == TipoCarta::SUMARCANTIDAD && jerarquia == 12){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarSumaClara(cartaElegida, indice);
        }

        if(cartaElegida.getAnverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarSumaClara(cartaElegida, indice);
        }
    }

    ResultadoJugada resultadoTirada;
    resultadoTirada.colorAviso = "#91042B";
    resultadoTirada.jugadaValida = false;
    return resultadoTirada;
}

/*====================  METODOS EN LOS QUE SE TIRAN LAS CARTAS =================*/
ResultadoJugada Partida::tirarCartaReversa(Carta& cartaElegida, int indice, bool adelante){

    ResultadoJugada resultadoTirada;

    Modelo* modeloActivo = adelante ? cartaElegida.getAnverso() : cartaElegida.getReverso();

    if(adelante){
        resultadoTirada.mensajeJugador = std::string("SE HA TIRADO LA CARTA ") + modeloActivo->getNombre();
    }else{
        resultadoTirada.mensajeJugador = std::string("SE HA TIRADO LA CARTA ") + modeloActivo->getNombre();
    }

    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 2000;

    modeloActivo->lanzarCarta(*this);

    Modelo* modeloActual;

    if(this->estaFlip){
        modeloActual = cartaElegida.getReverso();
    }else{
        modeloActual = cartaElegida.getAnverso();
    }

    TipoColor colorFinal = (modeloActual->getJerarquia() >= 13)
                               ? this->generarColorAleatorio()
                               : modeloActual->getColor().getColorCarta();

    this->establecerColorPartida(colorFinal);
    this->ordenCartas();

    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);

    resultadoTirada.tiempoAnimacion = 2500;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.requiereDecision = false;
    resultadoTirada.analizarStack = true;
    return  resultadoTirada;
}

ResultadoJugada Partida::tirarCartaNumericaClara(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;

    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 1500;
    resultadoTirada.mensajeJugador = std::string("Se ha tirado la carta ") + cartaElegida.getAnverso()->getNombre();
    TipoColor color = cartaElegida.getAnverso()->getColor().getColorCarta();
    this->establecerColorPartida(color);
    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);

    resultadoTirada.tiempoAnimacion = 2000;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.requiereDecision = false;
    resultadoTirada.analizarStack = true;
    return  resultadoTirada;
}

ResultadoJugada Partida::tirarBloqueoClara(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;
    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 3000;

    if(this->direccion == "Derecha"){
        resultadoTirada.mensajeJugador = std::string("Se ha tirado la carta ") + cartaElegida.getAnverso()->getNombre() + std::string(" al ") + this->listaJugadores.pickSiguiente()->getNombre();
        TipoColor color = cartaElegida.getAnverso()->getColor().getColorCarta();
        this->establecerColorPartida(color);
        cartaElegida.getAnverso()->lanzarCarta(*this,this->listaJugadores);

        this->pilaCentralCartas->push(cartaElegida);
        this->listaJugadores.pickAnterior()->getMazo()->eliminar(indice);

    }else if (this->direccion == "Izquierda"){
        resultadoTirada.mensajeJugador = std::string("Se ha tirado la carta ") + cartaElegida.getAnverso()->getNombre() + std::string(" al ") + this->listaJugadores.pickAnterior()->getNombre();
        TipoColor color = cartaElegida.getAnverso()->getColor().getColorCarta();
        this->establecerColorPartida(color);
        cartaElegida.getAnverso()->lanzarCarta(*this,this->listaJugadores);
        this->pilaCentralCartas->push(cartaElegida);
        this->listaJugadores.pickSiguiente()->getMazo()->eliminar(indice);
    }

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoAnimacion = 2000;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = true;
    return  resultadoTirada;
}

ResultadoJugada Partida::tirarCambioDireccionClara(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;
    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 3000;
    resultadoTirada.mensajeJugador = std::string("El ")+ this->listaJugadores.getActual()->getNombre() + std::string(" tiro la carta ") + cartaElegida.getAnverso()->getNombre() ;
    TipoColor color = cartaElegida.getAnverso()->getColor().getColorCarta();
    this->establecerColorPartida(color);
    cartaElegida.getAnverso()->lanzarCarta(*this,this->listaJugadores);
    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);
    this->inicioRonda = this->listaJugadores.getActual();
    this->setPuedeMoverse(false);

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoAnimacion = 2000;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = true;
    return  resultadoTirada;
}

ResultadoJugada Partida::tirarSumaClara(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;

    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 1500;
    resultadoTirada.mensajeJugador = std::string("Tiraste una carta ") + cartaElegida.getAnverso()->getNombre() ;
    TipoColor color = cartaElegida.getAnverso()->getColor().getColorCarta();
    this->establecerColorPartida(color);
    this->pilaCentralCartas->push(cartaElegida);
    this->pilaStacking->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoAnimacion = 2200;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = false;

    if(this->getJugadorActual()->getEstaObligado()){
        this->getJugadorActual()->setEstaObligado(false);
        this->getJugadorActual()->setTipoObligado(TipoCarta::Predeterminado);
    }

    return resultadoTirada;
}

/*==================== FIN DE LOS METODOS EN LOS QUE SE TIRAN LAS CARTAS =================*/

//Metodo utilizado para ejecutar la accion de cada carta oscura
ResultadoJugada Partida::ejecutarAccionCartaOscura(int indice){

    Carta cartaElegida = this->listaJugadores.getActual()->getMazo()->verValor(indice);

    ColorCarta color = cartaElegida.getReverso()->getColor().getColorCarta();

    Modelo * modeloPila = this->pilaCentralCartas->verTop().getReverso();

    int jerarquia = cartaElegida.getReverso()->getJerarquia();

    //Tiro de carta cambio de direccion de las cartas (reversa)
    if(jerarquia == -1 && this->configuracion.esFlip() && cartaElegida.getReverso()->getTipo() == TipoCarta::REVERSE){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarCartaReversa(cartaElegida, indice,false);
        }

        if(cartaElegida.getReverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarCartaReversa(cartaElegida, indice,false);
        }
    }

    if(jerarquia>= 0 &&  jerarquia<= 9){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarCartaNumericaOscura(cartaElegida,indice);
        }

        if(cartaElegida.getReverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarCartaNumericaOscura(cartaElegida,indice);
        }
    }

    if(cartaElegida.getReverso()->getTipo() == TipoCarta::SALTOTOTAL && jerarquia == 10){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarSaltoOscura(cartaElegida,indice);
        }

        if(cartaElegida.getReverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarSaltoOscura(cartaElegida,indice);
        }
    }

    if(cartaElegida.getReverso()->getTipo() == TipoCarta::CAMBIARDIRECCION && jerarquia == 11){

        if(jerarquia == modeloPila->getJerarquia()){
            return tirarCambioDireccionOscura(cartaElegida,indice);
        }

        if(cartaElegida.getReverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarCambioDireccionOscura(cartaElegida,indice);
        }
    }

    if(cartaElegida.getReverso()->getTipo() == TipoCarta::SUMARCANTIDAD && jerarquia == 12){


        if(jerarquia == modeloPila->getJerarquia()){
            return tirarSumaOscura(cartaElegida,indice);
        }

        if(cartaElegida.getReverso()->getColor().getColorCarta() == this->getColorPartida()){
            return tirarSumaOscura(cartaElegida,indice);
        }

    }

    ResultadoJugada resultadoTirada;
    resultadoTirada.jugadaValida = false;
    return resultadoTirada;

}

//===================REGION QUE PERMITE EJECUTAR EL CODIGO DE OSCURA=====================

ResultadoJugada Partida::tirarCartaNumericaOscura(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;
    //(P)
    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 1500;
    resultadoTirada.mensajeJugador = std::string("Se ha tirado la carta ") + cartaElegida.getReverso()->getNombre();
    TipoColor color = cartaElegida.getReverso()->getColor().getColorCarta();
    this->establecerColorPartida(color);
    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);
    resultadoTirada.tiempoAnimacion = 2000;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.requiereDecision = false;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = true;
    return resultadoTirada;

}
ResultadoJugada Partida::tirarSaltoOscura(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;
    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 3000;
    resultadoTirada.mensajeJugador = std::string("TIRASTE LA CARTA ")+ cartaElegida.getReverso()->getNombre() + ". TU TURNO!" ;
    TipoColor color = cartaElegida.getReverso()->getColor().getColorCarta();
    this->establecerColorPartida(color);
    cartaElegida.getReverso()->lanzarCarta(*this,this->listaJugadores);
    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);

    this->setPuedeMoverse(false);

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoAnimacion = 2000;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = true;
    return  resultadoTirada;
}

ResultadoJugada Partida::tirarCambioDireccionOscura(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;
    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 3000;
    resultadoTirada.mensajeJugador = std::string("El ")+ this->listaJugadores.getActual()->getNombre() + std::string(" tiro la carta ") + cartaElegida.getReverso()->getNombre() ;
    TipoColor color = cartaElegida.getReverso()->getColor().getColorCarta();
    this->establecerColorPartida(color);
    cartaElegida.getReverso()->lanzarCarta(*this,this->listaJugadores);
    this->pilaCentralCartas->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);
    this->setPuedeMoverse(false);

    resultadoTirada.tiempoAnimacion = 2000;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.requiereDecision = false;
    resultadoTirada.analizarStack = true;
    resultadoTirada.colorAviso = "#0C7527";

    return resultadoTirada;

}

ResultadoJugada Partida::tirarSumaOscura(Carta& cartaElegida, int indice){

    ResultadoJugada resultadoTirada;
    resultadoTirada.darMensaje = true;
    resultadoTirada.tiempoMensaje = 1500;
    resultadoTirada.mensajeJugador = std::string("Tiraste una carta ") + cartaElegida.getReverso()->getNombre() ;
    TipoColor color = cartaElegida.getReverso()->getColor().getColorCarta();
    this->establecerColorPartida(color);
    this->pilaCentralCartas->push(cartaElegida);
    this->pilaStacking->push(cartaElegida);
    this->listaJugadores.getActual()->getMazo()->eliminar(indice);

    resultadoTirada.requiereDecision = false;
    resultadoTirada.tiempoAnimacion = 2200;
    resultadoTirada.jugadaValida = true;
    resultadoTirada.colorAviso = "#0C7527";
    resultadoTirada.analizarStack = false;

    if(this->getJugadorActual()->getEstaObligado()){
        this->getJugadorActual()->setEstaObligado(false);
        this->getJugadorActual()->setTipoObligado(TipoCarta::Predeterminado);
    }

    return resultadoTirada;

}
//===================FALTA DE REGION QUE PERMITE EJECUTAR EL CODIGO DE OSCURA=====================

//Metodo que permite ejecutar la accion de aplicar todo el stack acumulado de cartas de suma
ResultadoJugada Partida::aplicarAcumuladas(){

    ResultadoJugada resultado;
    try{

        resultado.tiempoMensaje = 2000;
        resultado.darMensaje = true;
        int cantidad = this->pilaStacking->getLongitud();

        Carta cartaApilada = this->pilaStacking->verTop();

        while(!this->pilaStacking->estaVacia()){

            Carta cartaDesapilada = this->pilaStacking->verTop();

            if(!this->estaFlip){
                cartaDesapilada.getAnverso()->lanzarCarta(*this, this->listaJugadores);
            }
            else{
                cartaDesapilada.getReverso()->lanzarCarta(*this, this->listaJugadores);
            }

            this->pilaStacking->pop();
        }

        int vecesSuma = this->getVecesSumadasCarta();
        resultado.mensajeJugador = std::string("Se le han sumado ") + std::to_string(cantidad * vecesSuma) + " cartas";

        this->listaJugadores.getActual()->ordenarCartas(this->estaFlip);

        resultado.jugadaValida = true;
        resultado.tiempoAnimacion = 2500;
        resultado.colorAviso = "#091787";
        resultado.analizarStack = false;

        this->setVecesSumadasCarta(0);
        return resultado;

    }
    catch(const std::runtime_error & ex)
    {
        throw std::runtime_error("No se pudo desapilar el stack");
    }

    this->setVecesSumadasCarta(0);
    resultado.jugadaValida = false;
    return resultado;
}

//Metodo que le permitira al front realizar la peticion de cartas para ver si stackean
Pila<Carta> * Partida::getPilaStack()  {
    return this->pilaStacking;
}

//Metodo que le permitira al front realizar la peticion de cartas para ver si stackean
Pila<Carta> * Partida::getPilaLateral(){
    return this->pilaLateralCartas;
}

//Metodo utilizado para poder rellenar de nuevo la pila lateral
void Partida::llenarPilaLateral(){

    if (this->pilaCentralCartas->estaVacia()) return;

    Carta cartaEnMesa = this->pilaCentralCartas->verTop();
    this->pilaCentralCartas->pop();

    this->listadoCartas = new ListaEnlazada<Carta>();

    while (!this->pilaCentralCartas->estaVacia()) {
        this->listadoCartas->insertarFrente(this->pilaCentralCartas->verTop());
        this->pilaCentralCartas->pop();
    }

    this->pilaCentralCartas->push(cartaEnMesa);

    this->barajarCartas(this->listadoCartas);

    while (this->listadoCartas->getLongitud() > 0) {
        this->pilaLateralCartas->push(this->listadoCartas->popFront());
    }

    delete this->listadoCartas;
    this->listadoCartas = nullptr;
}

//Metodo que permite verificar si cuenta con cartas de suma par poder realizar la tirada
bool Partida::tieneCartasSumaStacking(){

    Carta cartaCentral = this->pilaStacking->verTop();
    ListaEnlazada<Carta>* mazo = this->listaJugadores.getActual()->getMazo();

    int cantidad = mazo->getLongitud();

    if(this->estaFlip){
        for(int i = 0; i < cantidad; i++){
            Carta cartaJugador = mazo->verValor(i);
            //ES SUMA DE COLOR
            if(cartaJugador.getReverso()->getJerarquia() == 12 && cartaJugador.getReverso()->getTipo() == TipoCarta::SUMARCANTIDAD){
                return true;
            }
        }
    }else{
        for(int i = 0; i < cantidad; i++){
            Carta cartaJugador = mazo->verValor(i);
            //ES SUMA DE COLOR
            if(cartaJugador.getAnverso()->getJerarquia() == 12 && cartaJugador.getAnverso()->getTipo() == TipoCarta::SUMARCANTIDAD){
                return true;
            }
        }
    }
    return false;
}

//Metodo que permite verificar si cuenta con cartas de suma par poder realizar la tirada
bool Partida::tieneCartasMulticolorStacking(){

    Carta cartaCentral = this->pilaStacking->verTop();
    ListaEnlazada<Carta>* mazo = this->listaJugadores.getActual()->getMazo();

    int cantidad = mazo->getLongitud();

    if(this->estaFlip){
        for(int i = 0; i < cantidad; i++){
            Carta cartaJugador = mazo->verValor(i);
            //ES SUMA MULTICOLOR
            if(cartaJugador.getReverso()->getJerarquia() == 13 && cartaJugador.getReverso()->getTipo() == TipoCarta::SUMAMULTICOLOR){
                return true;
            }
        }
    }else{
        for(int i = 0; i < cantidad; i++){
            Carta cartaJugador = mazo->verValor(i);
            //ES SUMA MULTICOLOR
            if(cartaJugador.getAnverso()->getJerarquia() == 13 && cartaJugador.getAnverso()->getTipo() == TipoCarta::SUMAMULTICOLOR){
                return true;
            }
        }
    }
    return false;
}

//Metodo que permite saber si un jugador ya solo tiene una carta
bool Partida::esUltimaCarta(Jugador * jugadorActual){
    int longitud = jugadorActual->getMazo()->getLongitud();
    return longitud == 1;
}



//Metodo que verifica si la carta tirada pertenece al mismo color (en claro)
bool Partida::esMismaClara(const Carta& cartaJugador, const Carta& cartaPila){

    // Coincide color ACTIVO
    if(cartaJugador.getAnverso()->getColor().getColorCarta() ==
        this->getColorPartida()){
        return true;
    }

    // Coincide jerarquia
    if(cartaJugador.getAnverso()->getJerarquia() ==
        cartaPila.getAnverso()->getJerarquia()){
        return true;
    }

    if(cartaJugador.getAnverso()->getJerarquia() >= 13){
        return true;
    }

    return false;
}

//Metodo que verifica si la carta tirada pertenece al mismo color (en oscuro)
bool Partida::esMismaOscura(const Carta& cartaJugador, const Carta& cartaPila){

    // Coincide color ACTIVO
    if(cartaJugador.getReverso()->getColor().getColorCarta() ==
        this->getColorPartida()){
        return true;
    }

    // Coincide jerarquia
    if(cartaJugador.getReverso()->getJerarquia() ==
        cartaPila.getReverso()->getJerarquia()){
        return true;
    }

    //Se tira la carta especial
    if(cartaJugador.getReverso()->getJerarquia() >= 13){
        return true;
    }

    return false;
}


//Metodo que le permite saber al programa si el usuario tiene la carta con el color necesario
bool Partida::tieneCartaNecesaria(){

    //Solo deja desapilar si en dado caso esta bajo el efecto de la carta de COLOR ETERNO
    if(this->getJugadorActual()->getObligadoSacar()){
        return false;
    }

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

        // Coincide color ACTIVO
        if(cartaJugador.getAnverso()->getColor().getColorCarta() ==
            this->getColorPartida()){
            return true;
        }

        // Coincide jerarquia
        if(cartaJugador.getAnverso()->getJerarquia() ==
            cartaCentral.getAnverso()->getJerarquia()){
            return true;
        }

        // Es comodin o carta especial superior
        if(cartaJugador.getAnverso()->getJerarquia() >= 13){
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

        // Coincide color ACTIVO
        if(cartaJugador.getReverso()->getColor().getColorCarta() ==
            this->getColorPartida()){
            return true;
        }

        // Coincide jerarquia
        if(cartaJugador.getReverso()->getJerarquia() ==
            cartaCentral.getReverso()->getJerarquia()){
            return true;
        }

        // Es comodin
        if(cartaJugador.getReverso()->getJerarquia() >= 13){
            return true;
        }
    }

    return false;
}


//Metodo que permite ejecutar la tirada
void Partida::ejecutarMovimiento(){

    this->getJugadorActual()->evaluarPropensoUno();

    if(this->direccion == "Derecha" && puedeMoverse){
        this->listaJugadores.avanzar();
        this->verificarVuelta();
    }
    else if(this->direccion == "Izquierda" && puedeMoverse){
        this->listaJugadores.retroceder();
        this->verificarVuelta();
    }
}

//Metodo que permite tomar el jugador siguiente al turno
Jugador * Partida::pickJugadorSiguiente(){

    if(this->direccion == "Derecha"){
        return this->listaJugadores.pickSiguiente();
    }
    else if(this->direccion == "Izquierda"){
        return this->listaJugadores.pickAnterior();
    }

    throw std::runtime_error(std::string( "No se ha podido obgener el jugador siguiente "));
}

//Metodo que permite tomar el jugador que estaba atras
Jugador * Partida::pickJugadorAnterior(){

    if(this->direccion == "Derecha"){
        return this->listaJugadores.pickAnterior();
    }
    else if(this->direccion == "Izquierda"){

        return this->listaJugadores.pickSiguiente();
    }

    throw std::runtime_error(std::string( "No se ha podido obgener el jugador anterior "));
}

//Metodo que permite determinar si ALGUN JUGADOR ESTA EN UNO
bool Partida::alguienEnUno() {

    for (int i = 0; i < listaJugadores.getLongitud(); ++i) {
        Jugador* jugadorEvaluado = listaJugadores.obtenerEn(i);

        if (jugadorEvaluado->getMazo()->getLongitud() == 1) {
            return true;
        }
    }
    return false;
}

//Metodo que permite verificar si ya se ha dado una vuelta
void Partida::verificarVuelta(){
    if(this->inicioRonda.getDato() == this->listaJugadores.getActual()){

        if(this->estaEclpse){
            this->setEstaEclipse(false);
            ordenCartas();
        }
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
//Metodo que permite obtener la configuracion de la partida
ConfiguracionPartida Partida::getConfiguracion(){
    return this->configuracion;
}

//Metodo util para frontend para que pueda saber el color en el que esta la partida
std::string Partida::getNombreColor(){
    return this->colorPartida;
}

//Metodos que permiten determinar si se puede robar
void Partida::setPuedeRetar(bool flag){
    this->puedeRetar = flag;
}
bool Partida::getPuedeRetar(){
    return this->puedeRetar;
}

//Metodos getter y setter PARA SABER LAS CARTAS SUMADAS
void Partida::setVecesSumadasCarta(int veces){
    this->vecesSumadasCarta = veces;
}
int Partida::getVecesSumadasCarta(){
    return this->vecesSumadasCarta;
}

//METODOS GETTER Y SETTER PARA SABER SI ESTA EL EFECTO ECLIPSE (MIO) :)
void Partida::setEstaEclipse(bool flag){
    this->estaEclpse = flag;
}
bool Partida::getEstaEclipse(){
    return this->estaEclpse;
}

//Metodo que permite retornar la lista de jugadores para la mecanica de CARTA ESPIA MIA (P)
ListaCircular<Jugador*>& Partida::getListaJugadoresPartida(){
    return this->listaJugadores;
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

    bool valeFlip = this->configuracion.esFlip();
    if(!valeFlip){
        return this->pilaLateralCartas->verTop().getAnverso()->getReversoModelo();
    }else{
        if(!this->estaFlip){
            return this->pilaLateralCartas->verTop().getReverso()->getPathImagen();
        }else{
            return this->pilaLateralCartas->verTop().getAnverso()->getPathImagen();
        }
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

    //Carta reversa (P)
    if(this->configuracion.esFlip()){
        this->modelosClaros[56] = new Reversa(ColorCarta(TipoColor::AZUL),"Reversa Azul","claro",-1);
        this->modelosClaros[57] = new Reversa(ColorCarta(TipoColor::AMARILLO),"Reversa Amarillo","claro",-1);
        this->modelosClaros[58] = new Reversa(ColorCarta(TipoColor::ROJO),"Reversa Rojo","claro",-1);
        this->modelosClaros[59] = new Reversa(ColorCarta(TipoColor::VERDE),"Reversa Verde","claro",-1);
    }
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
        j++;
    }

    j = 0;
    //Inicializacion de cartas numericas turquesas
    for (int i = 20; i < 30; i++) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::TURQUESA),arregloNombres[j],"oscuro",j,j);
        j++;
    }
    j = 0;
    //Inicializacion de cartas numericas violetas
    for (int i = 30; i < 40; i++) {
        this->modelosOscuros[i] = new Numerica(ColorCarta(TipoColor::VIOLETA),arregloNombres[j],"oscuro",j,j);
        j++;
    }

    //=======FIN INICIALIZACION CARTAS NUMERICAS=====


    //Generacion de las cartas oscuras +3
    this->modelosOscuros[40] = new SumaCantidad(ColorCarta(TipoColor::ROSA),"Mas tres Rosa","oscuro",12,3);
    this->modelosOscuros[41] = new SumaCantidad(ColorCarta(TipoColor::NARANJA),"Mas tres Naranja","oscuro",12,3);
    this->modelosOscuros[42] = new SumaCantidad(ColorCarta(TipoColor::VIOLETA),"Mas tres Violeta","oscuro",12,3);
    this->modelosOscuros[43] = new SumaCantidad(ColorCarta(TipoColor::TURQUESA),"Mas tres Turquesa","oscuro",12,3);
    //(P)
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

    //Carta reversa
    this->modelosOscuros[56] = new Reversa(ColorCarta(TipoColor::ROSA),"Reversa Rosa","oscuro",-1);
    this->modelosOscuros[57] = new Reversa(ColorCarta(TipoColor::NARANJA),"Reversa Naranja","oscuro",-1);
    this->modelosOscuros[58] = new Reversa(ColorCarta(TipoColor::VIOLETA),"Reversa Violeta","oscuro",-1);
    this->modelosOscuros[59] = new Reversa(ColorCarta(TipoColor::TURQUESA),"Reversa Turquesa","oscuro",-1);

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

    this->pilaStacking = new Pila<Carta>();

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

    if(this->configuracion.esFlip()){
        //Generar carta de reversa (P)
        for (int i = 0; i < 2; i++) {
            lista->insertarFrente(Carta(nullptr, this->modelosClaros[56], -1));
            lista->insertarFrente(Carta(nullptr, this->modelosClaros[57], -1));
            lista->insertarFrente(Carta(nullptr, this->modelosClaros[58], -1));
            lista->insertarFrente(Carta(nullptr, this->modelosClaros[59], -1));
        }
    }

}

//Metodo que permite armar las cartas del UNO FLIP
void Partida::armarCartasFlip(ListaEnlazada<Carta>*& lista){
    //(P)
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

        lista->insertarAtras(Carta(this->modelosOscuros[i],nullptr, modeloIndex));

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
            lista->insertarAtras(Carta(this->modelosOscuros[j],nullptr, modeloIndex));
            modeloIndex++;
        }

        if (modeloIndex >= 10) {
            modeloIndex = 1;
        }

        j++;
    } while (j < 40);


    //Generacion de las cartas +2
    for (int i = 0; i < 2; i++) {
        lista->insertarAtras(Carta( this->modelosOscuros[40],nullptr, 12));
        lista->insertarAtras(Carta( this->modelosOscuros[41], nullptr,12));
        lista->insertarAtras(Carta(this->modelosOscuros[42], nullptr, 12));
        lista->insertarAtras(Carta( this->modelosOscuros[43], nullptr,12));
    }


    //Generacion de las cartas cambio de direccion
    for (int i = 0; i < 2; i++) {
        lista->insertarAtras(Carta( this->modelosOscuros[44],nullptr, 11));
        lista->insertarAtras(Carta(this->modelosOscuros[45], nullptr,11));
        lista->insertarAtras(Carta( this->modelosOscuros[46],nullptr, 11));
        lista->insertarAtras(Carta(this->modelosOscuros[47],nullptr, 11));
    }

    //Generacion de las cartas cambio de salto total
    for (int i = 0; i < 2; i++) {
        lista->insertarAtras(Carta( this->modelosOscuros[48],nullptr, 10));
        lista->insertarAtras(Carta( this->modelosOscuros[49],nullptr, 10));
        lista->insertarAtras(Carta( this->modelosOscuros[50],nullptr, 10));
        lista->insertarAtras(Carta( this->modelosOscuros[51],nullptr, 10));
    }

    //Generar carta multicolor suma
    for (int i = 0; i < 4; i++) {
        lista->insertarAtras(Carta( this->modelosOscuros[52],nullptr, 13));
    }

    //Cartas comodin color eterno
    for (int i = 0; i < 4; i++) {
        lista->insertarAtras(Carta( this->modelosOscuros[53],nullptr, 14));
    }

    //Generar carta eclipse MIA (P)
    for (int i = 0; i < 4; i++) {
        lista->insertarAtras(Carta( this->modelosOscuros[54],nullptr, 15));
    }

    //Generar carta espia MIA (P)
    for (int i = 0; i < 4; i++) {
        lista->insertarAtras(Carta( this->modelosOscuros[55],nullptr, 16));
    }

    //Generar carta de reversa (P)
    for (int i = 0; i < 2; i++) {
        lista->insertarAtras(Carta( this->modelosOscuros[56],nullptr, -1));
        lista->insertarAtras(Carta(this->modelosOscuros[57],nullptr, -1));
        lista->insertarAtras(Carta(this->modelosOscuros[58],nullptr, -1));
        lista->insertarAtras(Carta(this->modelosOscuros[59],nullptr, -1));
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
    //(P)
    if(this->configuracion.esFlip()){
        for(int i = 0; i < 56; i++)
            delete modelosOscuros[i];
    }
//(P)
    delete this->pilaCentralCartas;
    delete this->pilaLateralCartas;

    if(this->pilaStacking != nullptr){
         delete this->pilaStacking;
    }
}

Partida::~Partida(){
    limpiarReferencias();
}

//CREATED BY (P.M)

