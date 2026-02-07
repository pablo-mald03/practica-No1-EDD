#include "pantallamodalidad.h"
#include "ui_pantallamodalidad.h"
#include "mainwindow.h"

PantallaModalidad::PantallaModalidad(DatosConfiguracion * &config,int cantidadPersonas, bool personalizacion, QWidget *parent)
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

    setChekedOpciones(config);
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

//metodo que setea por default todo lo de la UI
void PantallaModalidad::setChekedOpciones(DatosConfiguracion * &config){

    if (config == nullptr) {
        config = new DatosConfiguracion();
    }
    this->m_config = config;

    setSeleccion();

    this->m_config->stacking = true;
    this->m_config->retoMas4 = true;

    if (m_config) {

        ui->checkStacking->blockSignals(true);
        ui->checkMas4->blockSignals(true);
        //Se setean los valores de los checkbox
        ui->checkStacking->setChecked(this->m_config->stacking);
        ui->checkMas4->setChecked(this->m_config->retoMas4);

        ui->checkStacking->blockSignals(false);
        ui->checkMas4->blockSignals(false);
    }
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


void PantallaModalidad::on_checkStacking_toggled(bool checked)
{
    this->m_config->stacking = checked;
    ui->checkStacking->setChecked(this->m_config->stacking);

}

void PantallaModalidad::on_checkMas4_toggled(bool checked)
{
    this->m_config->retoMas4 = checked;
    ui->checkMas4->setChecked(this->m_config->retoMas4);
}


void PantallaModalidad::on_btnAvanzada_clicked()
{
    emit solicitarConfiguraciones();
}

