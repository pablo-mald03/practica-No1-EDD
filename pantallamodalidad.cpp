#include "pantallamodalidad.h"
#include "ui_pantallamodalidad.h"

PantallaModalidad::PantallaModalidad(int cantidadPersonas, bool personalizacion, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaModalidad ), cantidad(cantidadPersonas),personalizado(personalizacion)
{
    ui->setupUi(this);

    //Se activa el estilo
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al widget
    this->setStyleSheet("QWidget#PantallaModalidad { "
                        "border-image: url(:/assets/layoutsGame/LayoutConfigInicial.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

PantallaModalidad::~PantallaModalidad()
{
    delete ui;
}

void PantallaModalidad::on_btnRetorno_clicked()
{
    emit solicitarRegresoSeleccion();
}

