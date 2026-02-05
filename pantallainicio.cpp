#include "pantallainicio.h"
#include "ui_pantallainicio.h"

PantallaInicio::PantallaInicio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaInicio)
{
    ui->setupUi(this);

    //Se activa el estilo
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Aplicamos el estilo solo al padre (#) y usamos border-image para redimensionar
    this->setStyleSheet("QWidget#PantallaInicio { "
                        "border-image: url(:/assets/layoutsGame/LayoutInicial.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

PantallaInicio::~PantallaInicio()
{
    delete ui;
}
