#include "pantallajuego.h"
#include "ui_pantallajuego.h"
#include <QMessageBox>
#include <QString>
#include"mainwindow.h"

PantallaJuego::PantallaJuego(int _cantidad,bool &estaConfigurando,DatosConfiguracion * &config,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PantallaJuego)
{
    ui->setupUi(this);

    //Se activa el estilo
    this->setAttribute(Qt::WA_StyledBackground, true);

    //Se aplica el estilo al widget
    this->setStyleSheet("QWidget#PantallaJuego { "
                        "border-image: url(:/assets/layoutsGame/LayoutJuego.png) 0 0 0 0 stretch stretch; "
                        "} ");

    this->controladorPartida = new PartidaController(_cantidad,estaConfigurando,config,this);
    //Apartado donde se conectan los componentes a los metodos
    connect(this->controladorPartida, &PartidaController::datosPartida, this,&PantallaJuego::mostrarDatosPantalla);

    this->controladorPartida->obtenerDatosPartida();
    inicializarVistaMazo();
}
//Metodo que permite inicializar el widget del mazo
void PantallaJuego::inicializarVistaMazo(){
    escena = new QGraphicsScene(this);
    vista = new QGraphicsView(escena, this);
    vista->setStyleSheet("background: transparent; border: none;");
    vista->setRenderHint(QPainter::Antialiasing);

    if (this->ui->widgetMazo->layout()) {
        this->ui->widgetMazo->layout()->addWidget(vista);
    } else {
        QVBoxLayout *layoutInterno = new QVBoxLayout(this->ui->widgetMazo);
        layoutInterno->addWidget(vista);
    }
}

//Metodo que muestra los datos del jugador en pantalla
void PantallaJuego::mostrarDatosPantalla(Jugador* & jugadorActual, std::string direccion){

    this->ui->labelNombreJugador->setText(QString::fromStdString( jugadorActual->getNombre()));
    this->ui->labelVueltas->setText(QString::fromStdString(direccion));
    dibujarMazo(jugadorActual);
}

void PantallaJuego::dibujarMazo(Jugador* & jugadorActual){

}

PantallaJuego::~PantallaJuego()
{
    delete this->escena;
    this->escena = nullptr;
    delete this->vista;
    this->vista = nullptr;
    delete this->controladorPartida;
    this->controladorPartida = nullptr;
    delete ui;
}

void PantallaJuego::on_btnRetorno_clicked()
{
    auto respuesta = QMessageBox::question(this, "Salir de la partida", "¿Seguro que quieres salir de la partida?",
                                           QMessageBox::Yes | QMessageBox::No);
    if (respuesta == QMessageBox::Yes) {
       emit solicitarSalida();
    }

}

