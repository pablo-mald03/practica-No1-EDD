#include "pantallaconfiguraciones.h"
#include "ui_pantallaconfiguraciones.h"
#include"mainwindow.h"

PantallaConfiguraciones::PantallaConfiguraciones(bool &flag, DatosConfiguracion * &config,QWidget *parent)
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

    setChekedOpciones(config, flag);

}


//metodo que setea por default todo lo de la UI
void PantallaConfiguraciones::setChekedOpciones(DatosConfiguracion * &config, bool &flag){

    //Caso completo de excepcion pero se deja para no romper logica por cualquier fallo
    if (config == nullptr) {
        config = new DatosConfiguracion();

        this->a_config->stacking = true;
        this->a_config->retoMas4 = true;
    }
    this->a_config = config;

    if(!flag){
        this->a_config->modoRobo = true;
        this->a_config->gritoUno = true;
        this->a_config->ganarNegra = false;
        this->a_config->flip = false;
        flag = true;
    }


    if (this->a_config) {

        ui->checkRobo->blockSignals(true);
        ui->checkGrito->blockSignals(true);
        ui->checkGanarNegra->blockSignals(true);
        ui->checkBoxFlip->blockSignals(true);

        //Se setean los valores de los checkbox
        ui->checkRobo->setChecked(this->a_config->modoRobo);
        ui->checkGrito->setChecked(this->a_config->gritoUno);
        ui->checkGanarNegra->setChecked(this->a_config->ganarNegra);
        ui->checkBoxFlip->setChecked(this->a_config->flip);

        ui->checkRobo->blockSignals(false);
        ui->checkGrito->blockSignals(false);
        ui->checkGanarNegra->blockSignals(false);
        ui->checkBoxFlip->blockSignals(false);
    }
}


PantallaConfiguraciones::~PantallaConfiguraciones()
{
    delete ui;
}

void PantallaConfiguraciones::on_btnRetorno_clicked()
{
    emit solicitarRegresoModalidad();
}


void PantallaConfiguraciones::on_checkRobo_toggled(bool checked)
{
    this->a_config->modoRobo = checked;
    ui->checkRobo->setChecked(this->a_config->modoRobo);
}


void PantallaConfiguraciones::on_checkGrito_toggled(bool checked)
{
    this->a_config->gritoUno = checked;
    ui->checkGrito->setChecked(this->a_config->gritoUno);
}


void PantallaConfiguraciones::on_checkGanarNegra_toggled(bool checked)
{
    this->a_config->ganarNegra = checked;
    ui->checkGanarNegra->setChecked(this->a_config->ganarNegra);
}


void PantallaConfiguraciones::on_checkBoxFlip_toggled(bool checked)
{
    this->a_config->flip = checked;
    ui->checkBoxFlip->setChecked(this->a_config->flip);
}

