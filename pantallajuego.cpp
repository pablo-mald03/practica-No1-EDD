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

    qDebug() << "El valor de robo es: " << config->modoRobo;
    qDebug() << "El valor de flip es: " << config->flip;
    qDebug() << "El valor de mas 4 es: " << config->retoMas4;
    qDebug() << "El valor de stacking es: " << config->stacking;
    qDebug() << "El valor de ganar negra es: " << config->ganarNegra;
    qDebug() << "El valor de grito uno es: " << config->gritoUno;

    estaConfigurando = false;

    delete config;
    config = nullptr;

    qDebug() << "Se ha eliminado la configuracion ";

}

PantallaJuego::~PantallaJuego()
{
    delete ui;
}

void PantallaJuego::on_btnRetorno_clicked()
{
    auto respuesta = QMessageBox::question(this, "Salir", "¿Seguro que quieres salir de la partida?",
                                           QMessageBox::Yes | QMessageBox::No);
    if (respuesta == QMessageBox::Yes) {
       emit solicitarSalida();
    }

}

