#include "pantallajuego.h"
#include "ui_pantallajuego.h"
#include <QMessageBox>
#include <QString>
#include"cartadeckui.h"
#include"mainwindow.h"
#include"carta.h"
#include<QTimer>
#include "selectorcolordialog.h"
#include "vermazodialog.h"

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
    this->controladorPartida->obtenerDatosPartida(true);

    this->capaBloqueo = new QWidget(this);
    this->capaBloqueo->setStyleSheet("background: transparent;");
    this->capaBloqueo->hide();
}


//Metodo que permite verificar si el jugador anterior gano la partida (P)
void PantallaJuego::analizarGanador()
{
    bool yaGanaron = this->controladorPartida->jugadorGano();

    if(!yaGanaron){
        return;
    }

    capaBloqueo->setGeometry(this->rect());
    capaBloqueo->show();
    capaBloqueo->raise();

    this->controladorPartida->darMensajeGanador();


    QTimer::singleShot(4050, this, [this]() {
        capaBloqueo->hide();
        emit solicitarSalida();
    });
}

//Metodo que permite tirar la carta ESPIA Mecanica mia (P)
void PantallaJuego::mostrarMazoTemporal()
{
    bool flip = this->controladorPartida->estaModoFlip();
    VerMazoDialog dlg(this->controladorPartida->getListaJugadores(), flip, this);
    dlg.exec();

    this->controladorPartida->aplicarMovimiento();
}

//Metodo que permite evaluar si por lo menos uno de los jugadores esta en UNO
void PantallaJuego::evaluarJugadoresEnUno(){

    this->controladorPartida->refrescarEvaluacionUno();

    bool jugadorPropenso = this->controladorPartida->jugadorPropensoUno();
    bool alguienUno = this->controladorPartida->alguienEstaEnUno();

    if(jugadorPropenso || alguienUno){
        this->ui->btnUNO->setEnabled(true);
        this->ui->textoUNO->setEnabled(true);
    }else{
        this->ui->btnUNO->setEnabled(false);
        this->ui->textoUNO->setEnabled(false);
    }
}
//(P)
//Metodo que permite iniciar el timer que puede dar mensajes durante un tiempo
void PantallaJuego::instanciarTimer(){
    timerMensaje = new QTimer(this);

    timerMensaje->setSingleShot(true);

    // Cuando el timer termine, limpiamos el label
    connect(timerMensaje, &QTimer::timeout, [this]() {
        this->ui->labelMensajes->clear();
    });
}

//Metodo que permite seleccionar el color que se va a elegir  para el comodin
int PantallaJuego::mostrarSelectorColor(bool estaFlip)
{
    SelectorColorDialog dlg(estaFlip, this);

    if (dlg.exec() == QDialog::Accepted) {
        return dlg.getColorElegido();
    }

    return -1;
}

//Metodo que srive para poder dar mensajes en pantalla al jugador
void PantallaJuego::darMensajeJugador(std::string mensaje, QString colorHex, int tiempo){

    if (timerMensaje->isActive()) {
        timerMensaje->stop();
    }

    this->ui->labelMensajes->setText(QString::fromStdString(mensaje));

    this->ui->labelMensajes->setStyleSheet(
        "color: " + colorHex + "; font-size: 20px; font-weight: bold; font-family: \"Segoe UI\", Arial; background: transparent;padding: 2px; margin-bottom: 5px;");
    timerMensaje->start(tiempo);
//(P)
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
//(P)
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
//(P)
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

//Metodo de front que permite estar al tanto si se esta apilando una carta sumatoria
void PantallaJuego::verificarStacking(bool evaluar){

    if(!evaluar){
        return;
    }

    bool estaStacking =  this->controladorPartida->estaStackeando();

    if(!estaStacking){
        return;
    }
//(P)
    bool puedeStackear = this->controladorPartida->puedeStackear();

    if(!puedeStackear){
        ejecutarSumaCartas();
        return;
    }

    bool tieneCartasNecesarias = this->controladorPartida->tieneParaStackear();

    if(!tieneCartasNecesarias){
        ejecutarSumaCartas();
        return;
    }

    //Si llega hasta aca es porque si puede decidir si seguir stackeando
    std::string mensaje = this->controladorPartida->getMensajeStacking();

    bool decisionStackeo = mostrarConfirmacionStacking(mensaje);

    if(!decisionStackeo){
        ejecutarSumaCartas();
        return;
    }
//(P)
    this->darMensajeJugador("Selecciona tu carta para poder stackearla", "#0C7527",2000);
    this->controladorPartida->obligarJugador();
}

//Metodo de front que permite preguntarle al jugador si va a seguir stackeando
bool PantallaJuego::mostrarConfirmacionStacking(std::string mensaje) {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Tienes la posibilidad de apilar");
    msgBox.setText(QString::fromStdString(mensaje));

    // Botones personalizados
    QPushButton *btnSi = msgBox.addButton("¡Aceptar!", QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton("Paso", QMessageBox::NoRole);
    msgBox.setDefaultButton(btnNo);

    msgBox.setStyleSheet(
        "QMessageBox {"
        "  background-color: #2c3e50;"
        "  border: 2px solid #ecf0f1;"
        "}"
        "QLabel {"
        "  color: white;"
        "  font-size: 16px;"
        "  font-weight: bold;"
        "  padding: 10px;"
        "}"
        "QPushButton {"
        "  background-color: #34495e;"
        "  color: white;"
        "  border-radius: 5px;"
        "  padding: 8px 15px;"
        "  min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #e67e22;"
        "}"
        );

    msgBox.exec();

    if (msgBox.clickedButton() == btnSi) {
        return true;
    }
    return false;
}

//Metodo que ejecuta la suma de las cartas
void PantallaJuego::ejecutarSumaCartas(){

    capaBloqueo->setGeometry(this->rect());
    capaBloqueo->show();
    capaBloqueo->raise();

    ResultadoJugada resultado = this->controladorPartida->aplicarCartasStackeadas();

    if (!resultado.jugadaValida) {
        capaBloqueo->hide();
        return;
    }

    QTimer::singleShot(resultado.tiempoAnimacion, this, [this]() {
        this->controladorPartida->obtenerDatosPartida(true);
        capaBloqueo->hide();
    });

}

//Metodo que muestra los datos del jugador en pantalla
void PantallaJuego::mostrarDatosPantalla(Jugador* & jugadorActual, std::string direccion, int cartasPila, int vueltas, bool verificar, std::string colorPartida){

    this->ui->labelNombreJugador->setText(QString::fromStdString( jugadorActual->getNombre()));
    this->ui->labelVueltas->setText("Direccion: " + QString::fromStdString(direccion));
    this->ui->labelCantidadPila->setText("En pila: "+ QString::number(cartasPila));
    this->ui->labelVPartida->setText("Vueltas: "+ QString::number(vueltas));
    this->ui->labelColor->setText(QString::fromStdString(colorPartida));
    dibujarMazo(jugadorActual, verificar);
}

//Metodo que permite dibujar el mazo
void PantallaJuego::dibujarMazo(Jugador* & jugadorActual, bool verificar){

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

        bool estaEclipse = this->controladorPartida->getEstaEclipse();

        if(!estaEclipse){
            if(!estaEnFlip){
                visual = new CartaDeckUI(i, QString::fromStdString(cartaDeck.getAnverso()->getPathImagen()));
            }else{
                visual = new CartaDeckUI(i, QString::fromStdString(cartaDeck.getReverso()->getPathImagen()));
            }
        }
        else
        {
            if(estaEnFlip){
                visual = new CartaDeckUI(i, QString::fromStdString(cartaDeck.getAnverso()->getPathImagen()));
            }else{
                bool permiteFlip = this->controladorPartida->permiteFlip();
                if(!permiteFlip){
                    visual = new CartaDeckUI(i, QString::fromStdString(cartaDeck.getReverso()->getReversoModelo()));
                }
                else{
                    visual = new CartaDeckUI(i, QString::fromStdString(cartaDeck.getReverso()->getPathImagen()));
                }
            }
        }

        connect(visual, &CartaDeckUI::cartaClickeda, this, &PantallaJuego::onCartaPresionada);
        escena->addItem(visual);
        visual->setPos(xActual + (i * separacion), 30);
        visual->setZValue(i);
    }

    this->verificarStacking(verificar);
    this->evaluarJugadoresEnUno();
}

//Metodo que permite que la carta envie su signal para reportar que el jugador la quiere tirar
void PantallaJuego::onCartaPresionada(int indice) {

    try{
        capaBloqueo->setGeometry(this->rect());
        capaBloqueo->show();
        capaBloqueo->raise();

        ResultadoJugada resultado = this->controladorPartida->tirarCarta(indice);

        if (!resultado.jugadaValida) {
            capaBloqueo->hide();
            return;
        }

        if(resultado.esEspia){
            this->mostrarMazoTemporal();
            this->controladorPartida->obtenerDatosPartida(true);
            capaBloqueo->hide();
            analizarGanador();
            return;
        }

        if (resultado.requiereDecision) {
            capaBloqueo->hide();
            bool flip = this->controladorPartida->estaModoFlip();
            int seleccion = this->mostrarSelectorColor(flip);

            if(seleccion <= 0){
                capaBloqueo->hide();
                darMensajeJugador("HAS ELEGIDO UNA OPCION INVALIDA", "#91042B", 2000);
                return;
            }


            //METODO QUE SE ENCARGA DE HACER LA EJECUCION CUANDO EL JUGADOR DEBE ELEGIR UNA CARTA
            ResultadoJugada resultadoDecision = this->controladorPartida->decisionJugador(indice, seleccion);

            if (!resultadoDecision.jugadaValida) {
                capaBloqueo->hide();
                return;
            }

            QTimer::singleShot(resultadoDecision.tiempoAnimacion, this, [this]() {
                this->controladorPartida->obtenerDatosPartida(true);
                capaBloqueo->hide();
                analizarGanador();
            });
            return;
        }

        QTimer::singleShot(resultado.tiempoAnimacion, this, [this]() {
            this->controladorPartida->obtenerDatosPartida(true);
            capaBloqueo->hide();
            analizarGanador();
        });

    }catch(const std::runtime_error & ex){
        capaBloqueo->hide();
        darMensajeJugador(ex.what(), "#91042B", 2000);
    }
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
        this->darMensajeJugador("Tienes las cartas necesarias. No puedes desapilar","#91042B",2500);
        return;
    }

    capaBloqueo->setGeometry(this->rect());
    capaBloqueo->show();
    capaBloqueo->raise();

    try{
        //ResultadoJugada resultado = this->controladorPartida->tirarCarta(indice);

        ResultadoJugada resultado = this->controladorPartida->desapilarCarta();

        if (resultado.jugadaValida) {
            capaBloqueo->hide();
            return;
        }

        QTimer::singleShot(resultado.tiempoAnimacion, this, [this]() {
            this->controladorPartida->obtenerDatosPartida(true);
            capaBloqueo->hide();
        });
//(P)
    }catch(const std::runtime_error & ex){
        this->darMensajeJugador(ex.what(), "#91042B",2500);
        capaBloqueo->hide();
    }
}

//Boton para gritar UNO
void PantallaJuego::on_btnUNO_clicked()
{
    QString textoLimpio = ui->textoUNO->text().trimmed();
    this->controladorPartida->gritarUno(textoLimpio);
    this->ui->textoUNO->clear();
}

