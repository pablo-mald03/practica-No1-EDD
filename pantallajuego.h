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
//CREATED BY PABLO M
class PantallaJuego : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaJuego(int _cantidad,bool &estaConfigurando, DatosConfiguracion * &config,QWidget *parent = nullptr);
    ~PantallaJuego();

    //Metodo que permite que la carta genera una accion
    void onCartaPresionada(int indice);

private:
    Ui::PantallaJuego *ui;
    QGraphicsScene *escena;
    QGraphicsView *vista;

    //Atributo para poder controlar el tiempo
    QTimer* timerMensaje;

    //widget que bloquea acciones
    QWidget * capaBloqueo;

    PartidaController * controladorPartida = nullptr;
    int cantidadJugadores;

    //Metodos que comunican a la UI sus acciones
    void mostrarDatosPantalla(Jugador* & jugadorActual, std::string direccion, int cartasPila, int vueltas, bool verificar, std::string colorPartida);

    void inicializarVistaMazo();

    //Metodo para ilustrar el mazo del jugador
    void dibujarMazo(Jugador* & jugadorActual, bool verificar);

    //Metodo para preparar a la UI
    void prepararInterfazCartas();

    //Metodo para poder dibujar las cartas en los stacks centrales
    void actualizarPilaCentral(std::string rutaImagen);
    void actualizarBarajaLateral(std::string rutaImagenPila, int longitudPila);

    void darMensajeJugador(std::string mensaje, QString colorHex, int tiempo);

    //metodo para generar la instancia del timer
    void instanciarTimer();

    //Metodo que permite verificar el stacking de cartas
    void verificarStacking(bool evaluar);

    //Metodo que permite ejecutar la suma de las cartas de stackeo
    void ejecutarSumaCartas();

    //Metodo de front que permite preguntarle al jugador si va a seguir stackeando
    bool mostrarConfirmacionStacking(std::string mensaje);

    //Metodo que permite elegir un color al tirar comodines
    int mostrarSelectorColor(bool estaFlip);

    //Metodo que permite evaluar si por lo menos uno de los jugadores esta en UNO
    void evaluarJugadoresEnUno();

signals:
    void solicitarSalida();
private slots:
    void on_btnRetorno_clicked();

    void on_btnPilaLateral_clicked();
    void on_btnUNO_clicked();
};

#endif // PANTALLAJUEGO_H
