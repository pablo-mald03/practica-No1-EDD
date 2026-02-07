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

    setSeleccion();
}

//Metodos setter publicos
void PantallaModalidad::setCantidad(int valor){
    this->cantidad = valor;
}

void PantallaModalidad::setPersonalizacion(bool flag){
    this->personalizado = flag;
}

void PantallaModalidad::setSeleccion() {

    this->ui->spinBox1->setEnabled(this->personalizado);
    this->ui->spinBox1->setValue(this->cantidad);

}

PantallaModalidad::~PantallaModalidad()
{
    delete ui;
}

void PantallaModalidad::on_btnRetorno_clicked()
{
    this->ui->spinBox1->setEnabled(true);
    emit solicitarRegresoSeleccion();
}

