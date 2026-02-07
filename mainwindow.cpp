#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QGuiApplication>
#include <QStyle>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Instrucciones indicadas para poder abrir en mas de una pantalla
    QList<QScreen *> screens = QGuiApplication::screens();

    if (screens.size() > 1) {
        QScreen *segundaPantalla = screens.at(1);
        QRect geometria = segundaPantalla->availableGeometry();

        this->setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                this->size(),
                geometria
                )
            );
    } else {
        this->move(QGuiApplication::primaryScreen()->availableGeometry().center() - this->rect().center());
    }

    setCentralWidget(ui->gestorVentanas);

    this->estaConfigurando = false;

    this->inicio = new PantallaInicio(this);
    //Se agrega el widget
    ui->gestorVentanas->addWidget(this->inicio);

    ui->gestorVentanas->setCurrentWidget(this->inicio);

    connect(inicio, &PantallaInicio::solicitarSeleccion, this, &MainWindow::mostrarSeleccion);
}

//Metodo que permite ir a la pantalla de seleccion
void MainWindow::mostrarSeleccion() {

    if (!this->pantallaSelect) { // Si no existe, la creamos
        this->pantallaSelect = new PantallaSeleccion(this);
        ui->gestorVentanas->addWidget(this->pantallaSelect);

        //Se conectan las signls para poder cambiar de pantallas
        connect(this->pantallaSelect, &PantallaSeleccion::solicitarModalidad, this, &MainWindow::mostrarModalidad);

        connect(this->pantallaSelect, &PantallaSeleccion::solicitarRegresoInicio, this, [this](){
            this->estaConfigurando = false;
            ui->gestorVentanas->setCurrentWidget(this->inicio);
        });
    }
    ui->gestorVentanas->setCurrentWidget(this->pantallaSelect);
}

//Metodo para mostar Modalidad
void MainWindow::mostrarModalidad(int cantidadPersonas, bool personalizacion) {

    if (!this->pantallaModal) { // Si no existe, la creamos
        this->pantallaModal = new PantallaModalidad(this->datosConfig, cantidadPersonas,personalizacion, this);
        ui->gestorVentanas->addWidget(this->pantallaModal);

        //Se conectan las signls para poder cambiar de pantallas
        connect(this->pantallaModal, &PantallaModalidad::solicitarConfiguraciones, this, &MainWindow::mostrarConfiguraciones);


        //Signal que inicia el juego
        connect(this->pantallaModal, &PantallaModalidad::solicitarIniciarJuego, this, &MainWindow::mostrarJuego);

        connect(this->pantallaModal, &PantallaModalidad::solicitarRegresoSeleccion, this, [this](){
            this->pantallaModal->setChekedOpciones(this->datosConfig);
            this->estaConfigurando = false;
            ui->gestorVentanas->setCurrentWidget(this->pantallaSelect);
            vaciarPunteroDatos();
        });
    }else{
        this->pantallaModal->setCantidad(cantidadPersonas);
        this->pantallaModal->setPersonalizacion(personalizacion);
        this->pantallaModal->setSeleccion();
        this->pantallaModal->setChekedOpciones(this->datosConfig);
    }

    ui->gestorVentanas->setCurrentWidget(this->pantallaModal);
}

//Metodo para mostrar las configuraciones
void MainWindow::mostrarConfiguraciones() {

    if (!this->pantallaConfiguracion) { // Si no existe, la creamos
        this->pantallaConfiguracion = new PantallaConfiguraciones(this->estaConfigurando,this->datosConfig, this);
        ui->gestorVentanas->addWidget(this->pantallaConfiguracion);

        connect(this->pantallaConfiguracion, &PantallaConfiguraciones::solicitarRegresoModalidad, this, [this](){
            this->pantallaConfiguracion->setChekedOpciones(this->datosConfig,this->estaConfigurando);
            ui->gestorVentanas->setCurrentWidget(this->pantallaModal);
        });
    }else{
        this->pantallaConfiguracion->setChekedOpciones(this->datosConfig,this->estaConfigurando);
    }

    ui->gestorVentanas->setCurrentWidget(this->pantallaConfiguracion);
}


//Metodo para iniciar el juego
void MainWindow::mostrarJuego() {

    /*CODIGO QUE INICIA EL JUEGO DEFINITIVAMENTE*/

    qDebug() << "El valor de robo es: " << this->datosConfig->modoRobo;
    qDebug() << "El valor de flip es: " << this->datosConfig->flip;
    qDebug() << "El valor de mas 4 es: " << this->datosConfig->retoMas4;
    qDebug() << "El valor de stacking es: " << this->datosConfig->stacking;
    qDebug() << "El valor de ganar negra es: " << this->datosConfig->ganarNegra;
    qDebug() << "El valor de grito uno es: " << this->datosConfig->gritoUno;

}

//Metodo que se encarga de eliminar el puntero
void MainWindow::vaciarPunteroDatos(){
    if (this->datosConfig != nullptr) {
        delete this->datosConfig;
        this->datosConfig = nullptr;
    }
}

MainWindow::~MainWindow()
{
    vaciarPunteroDatos();
    delete ui;
}
