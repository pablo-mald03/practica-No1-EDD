#include "pantallaseleccion.h"
#include "ui_pantallaseleccion.h"

PantallaSeleccion::PantallaSeleccion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSeleccion)
{
    ui->setupUi(this);

    //Se activa el estilo
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al widget
    this->setStyleSheet("QWidget#PantallaSeleccion { "
                        "border-image: url(:/assets/layoutsGame/LayoutConfigInicial.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

PantallaSeleccion::~PantallaSeleccion()
{
    delete ui;
}

void PantallaSeleccion::on_btnRegreso_clicked()
{
    emit solicitarRegresoInicio();
}


void PantallaSeleccion::on_btnDosJugadores_clicked()
{
    emit solicitarModalidad(2,false);
}


void PantallaSeleccion::on_btnTresJugadores_clicked()
{
    emit solicitarModalidad(3,false);
}


void PantallaSeleccion::on_btnCuatroJugadores_clicked()
{
    emit solicitarModalidad(3,false);
}


void PantallaSeleccion::on_btnMasJugadores_clicked()
{
    emit solicitarModalidad(0,true);
}

