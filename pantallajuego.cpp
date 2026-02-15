#include "pantallajuego.h"
#include "ui_pantallajuego.h"
#include <QMessageBox>
#include <QString>
#include"cartadeckui.h"
#include"mainwindow.h"
#include"carta.h"

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

    this->controladorPartida = new PartidaController(_cantidad,estaConfigurando,config,this);
    //Apartado donde se conectan los componentes a los metodos
    connect(this->controladorPartida, &PartidaController::datosPartida, this,&PantallaJuego::mostrarDatosPantalla);
    connect(this->controladorPartida, &PartidaController::datosPilaCentral, this,&PantallaJuego::actualizarPilaCentral);
    connect(this->controladorPartida, &PartidaController::datosPilaLateral, this,&PantallaJuego::actualizarBarajaLateral);

    this->controladorPartida->obtenerDatosPartida();

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

//Metodo que se usa para poder preparar la UI para los eventos que registrara en juego
void PantallaJuego::prepararInterfazCartas() {

    this->ui->btnPilaLateral->setStyleSheet("border: none; background: transparent;");
    this->ui->btnPilaLateral->setCursor(Qt::PointingHandCursor);

    this->ui->labelStackedImg->setAlignment(Qt::AlignCenter);

    QPixmap pixReverso(":/assets/mediaGame/ReversoCarta.png");
    QIcon icono(pixReverso);
    this->ui->btnPilaLateral->setIcon(icono);
    this->ui->btnPilaLateral->setIconSize(this->ui->btnPilaLateral->size());

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

    if (longitudPila <= 0) {
        //this->ui->btnPilaLateral->hide();
        // O si prefieres que se vea el hueco vacío pero no se pueda clickear:
        this->ui->btnPilaLateral->setIcon(QIcon());
        this->ui->btnPilaLateral->setEnabled(false);
        return;
    }

    QPixmap pix(QString::fromStdString(rutaImagenPila));
    if (!pix.isNull()) {
        QIcon icono(pix);
        this->ui->btnPilaLateral->setIcon(icono);
        this->ui->btnPilaLateral->setIconSize(this->ui->btnPilaLateral->size());
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

    this->escena->clear(); // Limpia cartas anteriores

    int total = jugadorActual->getMazo()->getLongitud();
    if (total == 0) return;


    //Se configura el layout dinamico
    double anchoContenedor = this->vista->viewport()->width()-30;


    double anchoCarta = 135.0;
    double espacioDisponible = anchoContenedor - anchoCarta;

    double separacion;

    if (total == 1) {
        separacion = 0;
    } else {
        separacion = espacioDisponible / (total - 1);

        double solapamientoMaximo = 80.0;
        separacion = qMax(anchoCarta - solapamientoMaximo, separacion);
    }

    double anchoTotalCartas = anchoCarta + (total - 1) * separacion;
    double xActual = (anchoContenedor - anchoTotalCartas) / 2;

    for (int i = 0; i < total; ++i) {
        Carta cartaDeck = jugadorActual->getMazo()->getValor(i);

        CartaDeckUI* visual = new CartaDeckUI(i, QString::fromStdString( cartaDeck.getAnverso()->getPathImagen()));

        // Conectas la carta al slot de esta pantalla
        connect(visual, &CartaDeckUI::cartaClickeda, this, &PantallaJuego::onCartaPresionada);

        escena->addItem(visual);
        visual->setPos(xActual + (i * separacion), 300);
        visual->setZValue(i);
    }
}

//Metodo que permite que la carta envie su signal apra que sea eliminada del deck
void PantallaJuego::onCartaPresionada(int indice) {

    qDebug() << "Carta tocada con ID backend:" << indice;
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


void PantallaJuego::on_btnPilaLateral_clicked()
{

}

