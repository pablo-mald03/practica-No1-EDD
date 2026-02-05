#include "pantallainicio.h"
#include "ui_pantallainicio.h"

PantallaInicio::PantallaInicio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaInicio)
{
    ui->setupUi(this);
}

PantallaInicio::~PantallaInicio()
{
    delete ui;
}
