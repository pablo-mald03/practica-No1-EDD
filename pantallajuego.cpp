#include "pantallajuego.h"
#include "ui_pantallajuego.h"
#include <QMessageBox>
#include"mainwindow.h"

PantallaJuego::PantallaJuego(bool &estaConfigurando,DatosConfiguracion * &config,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaJuego)
{
    ui->setupUi(this);

    //Se activa el estilo
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al widget
    this->setStyleSheet("QWidget#PantallaJuego { "
                        "border-image: url(:/assets/layoutsGame/LayoutJuego.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->partida = new Partida(config);
    estaConfigurando = false;
}

PantallaJuego::~PantallaJuego()
{
    delete this->partida;
    delete ui;
}

void PantallaJuego::on_btnRetorno_clicked()
{
    auto respuesta = QMessageBox::question(this, "Salir de la partida", "¿Seguro que quieres salir de la partida?",
                                           QMessageBox::Yes | QMessageBox::No);
    if (respuesta == QMessageBox::Yes) {
       emit solicitarSalida();
    }

}

