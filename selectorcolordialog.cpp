#include "selectorcolordialog.h"
#include "ui_selectorcolordialog.h"

SelectorColorDialog::SelectorColorDialog(bool _estaFlip, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectorColorDialog), estaFlip(_estaFlip),colorElegido(-1)
{
    ui->setupUi(this);

    this->setStyleSheet(
        "QDialog#SelectorColorDialog {"
        "background: qlineargradient("
        "x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #1e272e,"
        "stop:1 #2f3640"
        ");"
        "}"
        );

    aplicarEstilos();
}

void SelectorColorDialog::aplicarEstilos(){

    QString estiloBase =
        "  border-radius: 15px;"
        "  border: 3px solid white;"
        "  color: white;"
        "  font-size: 18px;"
        "  font-weight: bold;"
        "  padding: 15px;";

    ui->btnColor1->setStyleSheet(estiloBase);
    ui->btnColor2->setStyleSheet(estiloBase);
    ui->btnColor3->setStyleSheet(estiloBase);
    ui->btnColor4->setStyleSheet(estiloBase);

    configurarColores(this->estaFlip);
}

//Metodo que permite retornar el color elegido
int SelectorColorDialog::getColorElegido() const {
    return colorElegido;
}

//Configura el color en base a las configuraciones
void SelectorColorDialog::configurarColores(bool estaFlip)
{

    QString colores[4];

    if (estaFlip) {
        colores[0] = "#df8901";
        colores[1] = "#83097f";
        colores[2] = "#05ad64";
        colores[3] = "#f57bf1";
    } else {
        colores[0] = "#e32730";
        colores[1] = "#081d9e";
        colores[2] = "#3e970e";
        colores[3] = "#f5c731";
    }

    ui->btnColor1->setStyleSheet(ui->btnColor1->styleSheet() + "background-color:" + colores[0] + ";");
    ui->btnColor2->setStyleSheet(ui->btnColor2->styleSheet() + "background-color:" + colores[1] + ";");
    ui->btnColor3->setStyleSheet(ui->btnColor3->styleSheet() + "background-color:" + colores[2] + ";");
    ui->btnColor4->setStyleSheet(ui->btnColor4->styleSheet() + "background-color:" + colores[3] + ";");
}

SelectorColorDialog::~SelectorColorDialog()
{
    delete ui;
}

void SelectorColorDialog::on_btnColor1_clicked()
{
    colorElegido = 1;
    accept();
}


void SelectorColorDialog::on_btnColor2_clicked()
{
    colorElegido = 2;
    accept();
}


void SelectorColorDialog::on_btnColor3_clicked()
{
    colorElegido = 3;
    accept();
}


void SelectorColorDialog::on_btnColor4_clicked()
{
    colorElegido = 4;
    accept();
}

