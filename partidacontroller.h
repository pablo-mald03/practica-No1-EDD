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

    ResultadoJugada decisionJugador(int indice, int decision);

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
