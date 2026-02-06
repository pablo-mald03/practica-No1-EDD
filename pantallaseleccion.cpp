#include "pantallaseleccion.h"
#include "ui_pantallaseleccion.h"

PantallaSeleccion::PantallaSeleccion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaSeleccion)
{
    ui->setupUi(this);

    //Se activa el estilo
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contend
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

