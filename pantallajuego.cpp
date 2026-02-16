#include "pantallajuego.h"
#include "ui_pantallajuego.h"
#include <QMessageBox>
#include <QString>
#include"cartadeckui.h"
#include"mainwindow.h"
#include"carta.h"
#include<QTimer>

//CREATED BY PABLO M

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

    inicializarVistaMazo();
    prepararInterfazCartas();
    instanciarTimer();


    this->controladorPartida = new PartidaController(_cantidad,estaConfigurando,config,this);
    //Apartado donde se conectan los componentes a los metodos
    connect(this->controladorPartida, &PartidaController::datosPartida, this,&PantallaJuego::mostrarDatosPantalla);
    connect(this->controladorPartida, &PartidaController::datosPilaCentral, this,&PantallaJuego::actualizarPilaCentral);
    connect(this->controladorPartida, &PartidaController::datosPilaLateral, this,&PantallaJuego::actualizarBarajaLateral);
    connect(this->controladorPartida, &PartidaController::darMensaje, this,&PantallaJuego::darMensajeJugador);
    this->controladorPartida->obtenerDatosPartida();

    this->capaBloqueo = new QWidget(this);
    this->capaBloqueo->setStyleSheet("background: transparent;");
    this->capaBloqueo->hide();
}

//Metodo que permite iniciar el timer que puede dar mensajes durante un tiempo
void PantallaJuego::instanciarTimer(){
    timerMensaje = new QTimer(this);

    timerMensaje->setSingleShot(true);

    // Cuando el timer termine, limpiamos el label
    connect(timerMensaje, &QTimer::timeout, [this]() {
        this->ui->labelMensajes->clear();
    });
}

//Metodo que srive para poder dar mensajes en pantalla al jugador
void PantallaJuego::darMensajeJugador(std::string mensaje){

    if (timerMensaje->isActive()) {
        timerMensaje->stop();
    }

    this->ui->labelMensajes->setText(QString::fromStdString(mensaje));

    timerMensaje->start(2500);

}

//Metodo que permite inicializar el widget del mazo
void PantallaJuego::inicializarVistaMazo(){
    escena = new QGraphicsScene(this);
    vista = new QGraphicsView(escena, this);

    // Alineación centrada para que el SceneRect(0,0,ancho,240) se vea bien
    vista->setAlignment(Qt::AlignCenter);

    vista->setStyleSheet("background: transparent; border: none;");
    vista->setRenderHint(QPainter::Antialiasing);

    // Evitamos scrollbars que alteran el ancho disponible
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if (this->ui->widgetMazo->layout()) {
        this->ui->widgetMazo->layout()->setContentsMargins(0,0,0,0);
        this->ui->widgetMazo->layout()->addWidget(vista);
    } else {
        QVBoxLayout *layoutInterno = new QVBoxLayout(this->ui->widgetMazo);
        layoutInterno->setContentsMargins(0,0,0,0);
        layoutInterno->addWidget(vista);
    }
}

//Metodo que se usa para poder preparar la UI para los eventos que registrara en juego
void PantallaJuego::prepararInterfazCartas() {

    this->ui->btnPilaLateral->setStyleSheet(
        "QPushButton { border: none; background: transparent; padding: 0px; margin: 0px; }"
        "QPushButton:disabled { color: white; border: none; background: transparent; }"
        );
    this->ui->btnPilaLateral->setCursor(Qt::PointingHandCursor);
    this->ui->labelStackedImg->setAlignment(Qt::AlignCenter);

    this->ui->labelStackedImg->setStyleSheet(
        "QLabel:disabled { color: white; }"
        );

    actualizarBarajaLateral(":/assets/mediaGame/ReversoCarta.png", 1);
}


//Metodo para ilustar la pila central con la primera carta
void PantallaJuego::actualizarPilaCentral(std::string rutaImagen){
    QPixmap pix(QString::fromStdString(rutaImagen));
    if (!pix.isNull()) {
        this->ui->labelStackedImg->setPixmap(pix.scaled(this->ui->labelStackedImg->size(),
                                                        Qt::KeepAspectRatio,
                                                        Qt::SmoothTransformation));
    }

}


//Metodo para actualizar la pila lateral
void PantallaJuego::actualizarBarajaLateral(std::string rutaImagenPila, int longitudPila){

    this->ui->btnPilaLateral->setIcon(QIcon());

    if (longitudPila <= 0) {
        this->ui->btnPilaLateral->setEnabled(false);
        return;
    }

    this->ui->btnPilaLateral->setEnabled(true);
    QPixmap pix(QString::fromStdString(rutaImagenPila));

    if (!pix.isNull()) {

        QSize tamanoObjetivo(165, 280);

        QPixmap pixEscalada = pix.scaled(tamanoObjetivo,
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);

        this->ui->btnPilaLateral->setIcon(QIcon(pixEscalada));
        this->ui->btnPilaLateral->setIconSize(tamanoObjetivo);
    }

}


//Metodo que muestra los datos del jugador en pantalla
void PantallaJuego::mostrarDatosPantalla(Jugador* & jugadorActual, std::string direccion, int cartasPila, int vueltas){

    this->ui->labelNombreJugador->setText(QString::fromStdString( jugadorActual->getNombre()));
    this->ui->labelVueltas->setText("Direccion: " + QString::fromStdString(direccion));
    this->ui->labelCantidadPila->setText("En pila: "+ QString::number(cartasPila));
    this->ui->labelVPartida->setText("Vueltas: "+ QString::number(vueltas));
    dibujarMazo(jugadorActual);
}

//Metodo que permite dibujar el mazo
void PantallaJuego::dibujarMazo(Jugador* & jugadorActual){

    this->escena->clear();

    int total = jugadorActual->getMazo()->getLongitud();
    if (total == 0) return;

    double anchoContenedor = this->vista->viewport()->width();
    if (anchoContenedor < 1241) anchoContenedor = 1241;

    double anchoCarta = 135.0;
    double ideal = (total > 1) ? (anchoContenedor - 30 - anchoCarta) / (total - 1) : 0;

    double separacion = (total > 1) ? qBound(25.0, ideal, 85.0) : 0;

    double anchoTotalCartas = anchoCarta + (total - 1) * separacion;
    double xActual = (anchoContenedor - anchoTotalCartas) / 2.0;

    this->escena->setSceneRect(0, 0, anchoContenedor, 240);

    for (int i = 0; i < total; ++i) {
        Carta cartaDeck = jugadorActual->getMazo()->getValor(i);

        bool estaEnFlip = this->controladorPartida->estaModoFlip();

        CartaDeckUI* visual = nullptr;
        if(!estaEnFlip){
            visual = new CartaDeckUI(i, QString::fromStdString(cartaDeck.getAnverso()->getPathImagen()));
        }else{
            visual = new CartaDeckUI(i, QString::fromStdString(cartaDeck.getReverso()->getPathImagen()));
        }

        connect(visual, &CartaDeckUI::cartaClickeda, this, &PantallaJuego::onCartaPresionada);

        escena->addItem(visual);
        visual->setPos(xActual + (i * separacion), 30);
        visual->setZValue(i);
    }
}

//Metodo que permite que la carta envie su signal para reportar que el jugador la quiere tirar
void PantallaJuego::onCartaPresionada(int indice) {

    capaBloqueo->setGeometry(this->rect());
    capaBloqueo->show();
    capaBloqueo->raise();

    this->controladorPartida->tirarCarta(indice);

    QTimer::singleShot(1500, this, [this]() {
        this->controladorPartida->obtenerDatosPartida();

        capaBloqueo->hide();
    });
}

PantallaJuego::~PantallaJuego()
{
    if (timerMensaje) {
        timerMensaje->stop();
        delete timerMensaje;
    }
    if(this->capaBloqueo){
        delete capaBloqueo;
    }

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


void PantallaJuego::on_btnPilaLateral_clicked()
{
    if(this->controladorPartida->puedeDesapilar()){
        this->darMensajeJugador("Tienes las cartas necesarias. No puedes desapilar");
        return;
    }

    try{

        this->controladorPartida->desapilarCarta();

    }catch(const std::runtime_error & ex){
        this->darMensajeJugador(ex.what());
    }


}

