#ifndef VERMAZODIALOG_H
#define VERMAZODIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QTimer>
#include"jugador.h"
#include"listacircular.h"

namespace Ui {
class VerMazoDialog;
}

class VerMazoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerMazoDialog(
        ListaCircular<Jugador*> jugadores,
        bool modoFlip,
        QWidget *parent = nullptr
        );
    ~VerMazoDialog();

private:
    Ui::VerMazoDialog *ui;

    ListaCircular<Jugador*> listaJugadores;
    bool estaFlip;

    QGraphicsScene* escena;
    QGraphicsView* vista;

    int jugadorSeleccionado;

    void inicializarVistaMazo();
    void cargarJugadores();
    void mostrarMazoJugador(int indice);
    void dibujarMazo(Jugador* jugadorActual);
};

#endif // VERMAZODIALOG_H
