#include "pantallainicio.h"
#include "ui_pantallainicio.h"
#include <QMessageBox>
#include<QApplication>

PantallaInicio::PantallaInicio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaInicio)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al contenedor padre
    this->setStyleSheet("QWidget#PantallaInicio { "
                        "border-image: url(:/assets/layoutsGame/LayoutInicial.png) 0 0 0 0 stretch stretch; "
                        "} ");
}

PantallaInicio::~PantallaInicio()
{
    delete ui;
}

void PantallaInicio::on_pushButton_2_clicked()
{
    auto respuesta = QMessageBox::question(this, "Salir", "¿Seguro que quieres abandonar salir de la aplicacion?",
                                           QMessageBox::Yes | QMessageBox::No);
    if (respuesta == QMessageBox::Yes) {
        QApplication::quit();
    }
}


void PantallaInicio::on_btnInicio_clicked()
{
    emit solicitarSeleccion();
}

