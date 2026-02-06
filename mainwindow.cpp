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

        // Se conectan las demas signals que esta pueda ejecutar para que sepa que hacer el main
        //connect(pantallaOpciones, &PantallaOpciones::solicitarConfiguracion, this, &MainWindow::mostrarConfiguracion);

        connect(this->pantallaSelect, &PantallaSeleccion::solicitarRegresoInicio, this, [this](){
            ui->gestorVentanas->setCurrentWidget(this->inicio);
        });
    }
    ui->gestorVentanas->setCurrentWidget(this->pantallaSelect);
}

MainWindow::~MainWindow()
{
    delete ui;
}
