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


public slots:
    void obtenerDatosPartida();
signals:
    void datosPartida(Jugador* &jugador,std::string direccion, int cartasPila, int vueltas);

};

#endif // PARTIDACONTROLLER_H
