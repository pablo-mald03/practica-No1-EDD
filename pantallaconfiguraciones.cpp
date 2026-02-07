#include "pantallaconfiguraciones.h"
#include "ui_pantallaconfiguraciones.h"

PantallaConfiguraciones::PantallaConfiguraciones(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaConfiguraciones)
{
    ui->setupUi(this);

    //Se activa el estilo
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al widget
    this->setStyleSheet("QWidget#PantallaConfiguraciones { "
                        "border-image: url(:/assets/layoutsGame/LayoutConfiguracionP.png) 0 0 0 0 stretch stretch; "
                        "} ");

}

PantallaConfiguraciones::~PantallaConfiguraciones()
{
    delete ui;
}
