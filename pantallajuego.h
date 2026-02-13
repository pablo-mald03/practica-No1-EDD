#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>

//Includes de C++
#include <QGraphicsScene>
#include <QGraphicsView>

//Include de la partida (INTEGRACION DE BACKEND)
#include"partidacontroller.h"
#include"jugador.h"

struct DatosConfiguracion;
namespace Ui {
class PantallaJuego;
}

class PantallaJuego : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaJuego(int _cantidad,bool &estaConfigurando, DatosConfiguracion * &config,QWidget *parent = nullptr);
    ~PantallaJuego();

private:
    Ui::PantallaJuego *ui;
    QGraphicsScene *escena;
    QGraphicsView *vista;

    PartidaController * controladorPartida = nullptr;
    int cantidadJugadores;

    //Metodos que comunican a la UI sus acciones
    void mostrarDatosPantalla(Jugador* & jugadorActual, std::string direccion);

    void inicializarVistaMazo();

    void dibujarMazo(Jugador* & jugadorActual);

signals:
    void solicitarSalida();
private slots:
    void on_btnRetorno_clicked();
};

#endif // PANTALLAJUEGO_H
