#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

void MainWindow::mostrarModalidad(int cantidadPersonas, bool personalizacion) {

    if (!this->pantallaModal) { // Si no existe, la creamos
        this->pantallaModal = new PantallaModalidad(cantidadPersonas,personalizacion, this);
        ui->gestorVentanas->addWidget(this->pantallaModal);

        //Se conectan las signls para poder cambiar de pantallas
       // connect(this->pantallaModal, &PantallaSeleccion::solicitarModalidad, this, &MainWindow::mostrarModalidad);

        connect(this->pantallaModal, &PantallaModalidad::solicitarRegresoSeleccion, this, [this](){
            ui->gestorVentanas->setCurrentWidget(this->pantallaSelect);
        });
    }
    ui->gestorVentanas->setCurrentWidget(this->pantallaModal);
}

MainWindow::~MainWindow()
{
    delete ui;
}
