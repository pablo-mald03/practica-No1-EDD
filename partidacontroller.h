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

    //Metodo utilzado para desapilar las cartas y agregarselas al jugador
    ResultadoJugada desapilarCarta();

public slots:

    void obtenerDatosPartida();
    void reportarMensaje(std::string mensaje, QString colorHex, int tiempo);

signals:
    void datosPartida(Jugador* &jugador,std::string direccion, int cartasPila, int vueltas);

    void datosPilaCentral(std::string direccion);

    void datosPilaLateral(std::string direccion, int cartasPila);

    void darMensaje(std::string mensaje, QString colorHex, int tiempo);


};

#endif // PARTIDACONTROLLER_H
