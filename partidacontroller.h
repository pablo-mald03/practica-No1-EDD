#ifndef PARTIDACONTROLLER_H
#define PARTIDACONTROLLER_H

#include <QObject>
#include"partida.h"

//CLASE QUE ES EL PUENTE INTERMEDIO ENTRE EL BACKEND Y FRONTEND. DA ORDENES A BACKEND Y EMITE A FRONT

class PartidaController:public QObject
{
    Q_OBJECT

private:
    Partida * gestorPartida;

public:
    explicit PartidaController(int _cantidad,bool &estaConfigurando, DatosConfiguracion * &config, QObject* parent = nullptr);
    ~PartidaController();

    //Metodos que comunican a la UI con el backend
    ResultadoJugada tirarCarta(int indice);
    bool estaModoFlip();

    //Metodo que verifica si el jugador puede desapilar
    bool puedeDesapilar();

    //Metodo que comunica a front si se esta stackeando
    bool estaStackeando();

    //Metodo que permite dar el aviso para que se apliquen todas las cartas del stack al jugador
    ResultadoJugada aplicarCartasStackeadas();

    //Metodo que le permite saber a front si puede stackear
    bool puedeStackear();

    //Metodo que sirve para verificar si el usuario tiene cartas para poder seguir stackeando
    bool tieneParaStackear();

    //Metodo utilzado para desapilar las cartas y agregarselas al jugador
    ResultadoJugada desapilarCarta();

    //Permite obtener el mensaje de pregunta SI SOLO SI SE PUEDE STACKEAR
    std::string getMensajeStacking();

    //Metodo que le obliga al jugador a solo tirar un tipo
    void obligarJugador();

    //Ejecuta la decision del jugador al elegir un color
    ResultadoJugada decisionJugador(int indice, int decision);

    //Metodo que permite setear el color de la partida de fonra independiente
    void setearColorPartida(int decision);

    //Metodo que permite saber si esta activado el eclipse
    bool getEstaEclipse();

    //Metodo que permite evaluar si la partida admite cambiar a FLIP
    bool permiteFlip();

    //Metodo que permite evaluar en todo momento si el jugador esta propenso a quedar en UNO
    bool jugadorPropensoUno();

    //Metodo que evalua si minimo uno de los jugadores en partida esta en UNO (Para habilitar el boton)
    bool alguienEstaEnUno();

    //Metodo que permite ejecutar la accion de poder gritar UNO
    void gritarUno(QString mensaje);

    //Metodo que permite evaluar si el  jugador esta propenso cada que refresca
    void refrescarEvaluacionUno();

    //Metodo que permite retornar la lista de jugadores
    ListaCircular<Jugador*>& getListaJugadores();

    //Metodo que permite mover a la lista desde el front (CASO MUY ESPECIAL CUANDO ES ESPIA)
    void aplicarMovimiento();

    //Metodo que permite retornar si el jugador ya gano
    bool jugadorGano();

    //Metodo que permite retornar el mensaje para el jugador ganador
    void darMensajeGanador();

    //Metodo que permite verificar si el jugador puede retar
    bool puedeRetar();

    //Metodo que verifica si esta stackeando comodines
    bool estaStackeandoComodin();

    //Metodo que permite obligar al jugador a retar
    void obligarRetar();

    //Metodo para retar al jugador anterior
    void retarJugador();

public slots:

    void obtenerDatosPartida(bool verificar);
    void reportarMensaje(std::string mensaje, QString colorHex, int tiempo);

signals:
    void datosPartida(Jugador* &jugador,std::string direccion, int cartasPila, int vueltas, bool verificar, std::string colorPartida);

    void datosPilaCentral(std::string direccion);

    void datosPilaLateral(std::string direccion, int cartasPila);

    void darMensaje(std::string mensaje, QString colorHex, int tiempo);


};

#endif // PARTIDACONTROLLER_H
