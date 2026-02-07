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

        connect(this->pantallaModal, &PantallaModalidad::solicitarRegresoSeleccion, this, [this](){
            ui->gestorVentanas->setCurrentWidget(this->pantallaSelect);
            this->pantallaModal->setChekedOpciones(this->datosConfig);
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
        this->pantallaConfiguracion = new PantallaConfiguraciones(this->datosConfig, this);
        ui->gestorVentanas->addWidget(this->pantallaConfiguracion);

        //Se conectan las signls para poder cambiar de pantallas
        // connect(this->pantallaModal, &PantallaSeleccion::solicitarModalidad, this, &MainWindow::mostrarModalidad);

        connect(this->pantallaConfiguracion, &PantallaConfiguraciones::solicitarRegresoModalidad, this, [this](){
            ui->gestorVentanas->setCurrentWidget(this->pantallaModal);
            /*this->pantallaModal->setChekedOpciones(this->datosConfig);
            vaciarPunteroDatos();*/
        });
    }else{
       /* this->pantallaModal->setCantidad(cantidadPersonas);
        this->pantallaModal->setPersonalizacion(personalizacion);
        this->pantallaModal->setSeleccion();
        this->pantallaModal->setChekedOpciones(this->datosConfig);*/
    }

    ui->gestorVentanas->setCurrentWidget(this->pantallaConfiguracion);
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
