#include "pantallaconfiguraciones.h"
#include "ui_pantallaconfiguraciones.h"
#include"mainwindow.h"

PantallaConfiguraciones::PantallaConfiguraciones(DatosConfiguracion * &config,QWidget *parent)
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


//metodo que setea por default todo lo de la UI
void PantallaConfiguraciones::setChekedOpciones(DatosConfiguracion * &config){

    //Caso completo de excepcion pero se deja para no romper logica por cualquier fallo
    if (config == nullptr) {
        config = new DatosConfiguracion();

        this->a_config->stacking = true;
        this->a_config->retoMas4 = true;
    }
    this->a_config = config;

    this->a_config->modoRobo = true;
    this->a_config->gritoUno = true;
    this->a_config->ganarNegra = false;

    /*


    if (m_config) {

        ui->checkStacking->blockSignals(true);
        ui->checkMas4->blockSignals(true);
        //Se setean los valores de los checkbox
        ui->checkStacking->setChecked(this->m_config->stacking);
        ui->checkMas4->setChecked(this->m_config->retoMas4);

        ui->checkStacking->blockSignals(false);
        ui->checkMas4->blockSignals(false);
    }*/
}

PantallaConfiguraciones::~PantallaConfiguraciones()
{
    delete ui;
}

void PantallaConfiguraciones::on_btnRetorno_clicked()
{
    emit solicitarRegresoModalidad();
}

