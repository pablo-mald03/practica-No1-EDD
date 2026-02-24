#include "partidacontroller.h"
#include <qdebug.h>

PartidaController::PartidaController(int _cantidad,bool &estaConfigurando, DatosConfiguracion * &config, QObject* parent)
    :QObject(parent)
{

    estaConfigurando = false;
    this->gestorPartida= new Partida(_cantidad,config);
}

PartidaController::~PartidaController(){

    delete this->gestorPartida;
    this->gestorPartida = nullptr;
}

//Metodo que permite retornar la lista de jugadores para la mecanica de CARTA ESPIA MIA (P)
ListaCircular<Jugador*>& PartidaController::getListaJugadores(){
    return this->gestorPartida->getListaJugadoresPartida();
}

//Metodo que evalua constantemente si el jugador esta propenso
void PartidaController::refrescarEvaluacionUno(){
    this->gestorPartida->getJugadorActual()->evaluarPropensoUno();
}

//Metodo que permite evaluar en todo momento si el jugador esta propenso a quedar en UNO
bool PartidaController::jugadorPropensoUno(){
    return this->gestorPartida->getJugadorActual()->estaPropensoUno() && this->gestorPartida->tieneCartaNecesaria();
}

//Metodo que permite evaluar si POR LO  MENOS ALGUN JUGADOR ESTA en UNO
bool PartidaController::alguienEstaEnUno(){
    return this->gestorPartida->alguienEnUno();
}


//(P)
//Metodo que permite saber si el backend esta stackeando
bool PartidaController::estaStackeando(){

    Pila<Carta> * pilaStack = this->gestorPartida->getPilaStack();

    if(pilaStack == nullptr){
        return false;
    }

    if(pilaStack->estaVacia()){
        return false;
    }

    return true;
}
//METODO EXCLUSIVO DE LA CARTA ESPIA QUE EJECUTA MOVIMIENTO DESPUES
void PartidaController::aplicarMovimiento(){
    this->gestorPartida->ejecutarMovimiento();
}

//Metodo que permite dar el aviso para que se apliquen todas las cartas del stack al jugador
ResultadoJugada PartidaController::aplicarCartasStackeadas(){

    ResultadoJugada resultado;

    try{ //(P)
        //Metodo principal
        resultado = this->gestorPartida->aplicarAcumuladas();

        if (resultado.jugadaValida) {

            //Acciones antes de refrescar
            this->obtenerDatosPartida(resultado.analizarStack);

            if(resultado.darMensaje){
                QString color = QString::fromStdString(resultado.colorAviso);
                reportarMensaje(resultado.mensajeJugador, color, resultado.tiempoMensaje);
            }

            return resultado;

        } else {
            reportarMensaje("No se pudo aplicar las sumas de las cartas", "#91042B", 2500);
        }

    }catch(const std::runtime_error & ex){
        reportarMensaje(ex.what(), "#91042B", 2500);
    }

    resultado.jugadaValida = false;
    return resultado;
}

//Metodo que le permite saber a front si puede stackear
bool PartidaController::puedeStackear(){
    bool flag = this->gestorPartida->getConfiguracion().esStacking();
    return flag;
}

//Metodo que permite limitar al jugador que solo puede tirar una carta
void PartidaController::obligarJugador(){

    Jugador * jugadorActual = this->gestorPartida->getJugadorActual();
    Carta cartaAcual = this->gestorPartida->getPilaStack()->verTop();

    jugadorActual->setEstaObligado(true);

    if(this->estaModoFlip()){
        TipoCarta tipoCarta = cartaAcual.getReverso()->getTipo();
        jugadorActual->setTipoObligado(tipoCarta);
    }else{
        TipoCarta tipoCarta = cartaAcual.getAnverso()->getTipo();
        jugadorActual->setTipoObligado(tipoCarta);
    }

}
//(P)
//Metodo que permite setear el color elegido por el usuario de forma independiente
void PartidaController::setearColorPartida(int decision){

    try{
        //Metodo principal
        ResultadoJugada jugadaNormal;

        jugadaNormal.darMensaje = true;
        jugadaNormal.tiempoMensaje = 1500;
        jugadaNormal.jugadaValida = true;

        this->gestorPartida->setColorJuegoSelect(jugadaNormal, decision);

        if (jugadaNormal.jugadaValida) {

            jugadaNormal.analizarStack = false;

            //Acciones antes de refrescar
            this->obtenerDatosPartida(jugadaNormal.analizarStack);

            if(jugadaNormal.darMensaje){
                QString color = QString::fromStdString(jugadaNormal.colorAviso);
                reportarMensaje(jugadaNormal.mensajeJugador, color, jugadaNormal.tiempoMensaje);
            }

            return;

        } else {
            reportarMensaje("No se pudo establecer el color", "#91042B", 2500);
        }

    }catch(const std::runtime_error & ex){
        reportarMensaje(ex.what(), "#91042B", 2500);
    }
}

//Metodo que permite saber si esta activado el eclipse
bool PartidaController::getEstaEclipse(){
    return this->gestorPartida->getEstaEclipse();
}

//Metodo que permite verificar si tiene las cartas para volver a stackear
bool PartidaController::tieneParaStackear(){

    Pila<Carta> * pilaStack = this->gestorPartida->getPilaStack();//(P)

    Carta cartaEnStack = pilaStack->verTop();

    if(cartaEnStack.getAnverso()->getTipo() == TipoCarta::SUMARCANTIDAD){
        return this->gestorPartida->tieneCartasSumaStacking();
    }
    else if(cartaEnStack.getAnverso()->getTipo() == TipoCarta::SUMAMULTICOLOR){
        return this->gestorPartida->tieneCartasMulticolorStacking();
    }

    return false;
}

//Permite obtener el mensaje de pregunta SI SOLO SI SE PUEDE STACKEAR
std::string PartidaController::getMensajeStacking(){

    Pila<Carta> * pilaStack = this->gestorPartida->getPilaStack();

    bool estaFlip = this->estaModoFlip();

    int cantidad = pilaStack->getLongitud();

    if(!estaFlip){
        return std::string("Hay ") + std::to_string(cantidad) + std::string(" de cartas ")+ pilaStack->verTop().getAnverso()->getNombre();

    }else{
        return std::string("Hay ") + std::to_string(cantidad) + std::string(" de cartas ")+ pilaStack->verTop().getReverso()->getNombre();
    }//(P)
}

//Metodo que comunica a front que hacer si se esta en modo flip
bool PartidaController::estaModoFlip(){
    return this->gestorPartida->getEstaFlip();
}

//Metodo que permite dar la accion de poder seleccionar un valor para establecer un color
ResultadoJugada PartidaController::decisionJugador(int indice, int decision){

    try{
        //Metodo principal
        ResultadoJugada jugadaNormal = this->gestorPartida->ejecutarDecision(indice, decision);

        if (jugadaNormal.jugadaValida) {

            //Acciones antes de refrescar
            this->obtenerDatosPartida(jugadaNormal.analizarStack);

            this->gestorPartida->ejecutarMovimiento();

            bool puedeMoverse =this->gestorPartida->getPuedeMoverse();

            if(!puedeMoverse){
                this->gestorPartida->setPuedeMoverse(true);
            }

            if(jugadaNormal.darMensaje){
                QString color = QString::fromStdString(jugadaNormal.colorAviso);
                reportarMensaje(jugadaNormal.mensajeJugador, color, jugadaNormal.tiempoMensaje);
            }

            return jugadaNormal;

        } else {
            reportarMensaje("No se pudo tomar la decision", "#91042B", 2500);
        }

    }catch(const std::runtime_error & ex){
        reportarMensaje(ex.what(), "#91042B", 2500);
    }

    ResultadoJugada jugadaNormal;
    jugadaNormal.jugadaValida = false;

    return jugadaNormal;
}


//Metodo que permite ejecutar la accion y comunicarse con el backend de cuando el jugador en pantalla tira una carta
ResultadoJugada PartidaController::tirarCarta(int indice){
    try{
        //Metodo principal
        ResultadoJugada jugadaNormal = this->gestorPartida->ejecutarTirada(indice);

        if (jugadaNormal.jugadaValida) {

            //Acciones antes de refrescar
            this->obtenerDatosPartida(jugadaNormal.analizarStack);

            this->gestorPartida->ejecutarMovimiento();

            bool puedeMoverse =this->gestorPartida->getPuedeMoverse();

            if(!puedeMoverse){
                this->gestorPartida->setPuedeMoverse(true);
            }

            if(jugadaNormal.darMensaje){
                QString color = QString::fromStdString(jugadaNormal.colorAviso);
               reportarMensaje(jugadaNormal.mensajeJugador, color, jugadaNormal.tiempoMensaje);
            }

            return jugadaNormal;

        } else {

            if(jugadaNormal.darMensaje){
                QString color = QString::fromStdString(jugadaNormal.colorAviso);
                reportarMensaje(jugadaNormal.mensajeJugador, color, jugadaNormal.tiempoMensaje);
            }else{
                reportarMensaje("Esa carta no se puede tirar", "#91042B", 2500);
            }
        }

    }catch(const std::runtime_error & ex){
        reportarMensaje(ex.what(), "#91042B", 2500);
    }

    ResultadoJugada jugadaNormal;
    jugadaNormal.jugadaValida = false;

    return jugadaNormal;
}

//Metodo utilizado para que el jugador grite UNO
void PartidaController::gritarUno(QString mensaje){

    try{

        std::string mensajeString = mensaje.toStdString();
        std::string mensajeAccion = this->gestorPartida->gritarUno(mensajeString);
        reportarMensaje(mensajeAccion, "#0C7527", 2500);
        this->obtenerDatosPartida(true);

    }catch(const std::runtime_error & ex){
        reportarMensaje(ex.what(), "#91042B", 2500);
    }

}

//======METODOS QUE RETORNAN SI EL JUGADOR YA GANO (METODOS COMPLEMENTARIOS)========
bool PartidaController::jugadorGano(){
    Jugador * jugadorAnterior = this->gestorPartida->pickJugadorAnterior();
    return jugadorAnterior->getMazo()->getLongitud() == 0;
}

void PartidaController::darMensajeGanador(){
    Jugador * jugadorAnterior = this->gestorPartida->pickJugadorAnterior();
    std::string mensaje = std::string("!EL ") + jugadorAnterior->getNombre() + std::string(" HA GANADO LA PARTIDA!");
    reportarMensaje(mensaje, "#0C7527", 4000);
}

//======METODOS QUE RETORNAN SI EL JUGADOR YA GANO (METODOS COMPLEMENTARIOS)========

//Metodo util para verificar si puede desapilar
bool PartidaController::puedeDesapilar(){
    return this->gestorPartida->tieneCartaNecesaria();
}

//Metodo util para saber si se puede establecer flip
bool PartidaController::permiteFlip(){
    return this->gestorPartida->getConfiguracion().esFlip();
}

//Metodo utilzado para que el usuario pueda desapilar una carta
ResultadoJugada PartidaController::desapilarCarta(){

    ResultadoJugada resultadoJugada = this->gestorPartida->tomarCarta();

    if(resultadoJugada.jugadaValida){
        this->obtenerDatosPartida(resultadoJugada.analizarStack);
        return resultadoJugada;

    }else{
        this->obtenerDatosPartida(resultadoJugada.analizarStack);

        this->gestorPartida->ejecutarMovimiento();

        if(resultadoJugada.darMensaje){
            QString color = QString::fromStdString(resultadoJugada.colorAviso);
            reportarMensaje(resultadoJugada.mensajeJugador, color, resultadoJugada.tiempoMensaje);
        }

        return resultadoJugada;
    }
}


//Metodo que permite soltar mensajes en la ui de avisos
void PartidaController::reportarMensaje(std::string mensaje, QString colorHex, int tiempo){
    emit darMensaje(mensaje,colorHex, tiempo);
}

//======APARTADO DONDE EL JUGADOR PUEDE RETAR O NO
bool PartidaController::puedeRetar(){
    return this->gestorPartida->getConfiguracion().esRetoMas4();
}

bool PartidaController::estaStackeandoComodin(){
    Carta cartaStack = this->gestorPartida->getPilaStack()->verTop();

    bool esFlip = this->estaModoFlip();

    if(!esFlip){
        return cartaStack.getAnverso()->getJerarquia() == 13;
    }else{
        return cartaStack.getReverso()->getJerarquia() == 13;
    }
}

//Metodo que obliga al jugador actual a retar
void PartidaController::obligarRetar(){
    this->gestorPartida->obligarJugadorRetar();
}

//Metodo que permite ejecutar el reto al jugador anterior
void PartidaController::retarJugador(){
    std::string mensaje = this->gestorPartida->ejecutarReto();
    this->obtenerDatosPartida(false);
    reportarMensaje(mensaje, "#091787", 2000);
}

//======APARTADO DONDE EL JUGADOR PUEDE RETAR O NO


//(P)
//Metodo que se encarga de retornar la informacion principal al iniciar la partida
void PartidaController::obtenerDatosPartida(bool verificar){
    emit datosPartida(this->gestorPartida->getJugadorActual(),this->gestorPartida->getDireccion(), this->gestorPartida->getCantidadPila(), this->gestorPartida->getCantidadVueltas(),verificar,this->gestorPartida->getNombreColor());
    emit datosPilaCentral(this->gestorPartida->imagenPilaCentral());
    emit datosPilaLateral(this->gestorPartida->imagenPilaLateral(), this->gestorPartida->getCantidadPila());

}
