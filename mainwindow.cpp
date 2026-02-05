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

    // int indiceActual = ui->gestorVentanas->currentIndex();
    //connect(inicio, &PantallaInicio::solicitarRegistro, this, &MainWindow::mostrarRegistro);
}

MainWindow::~MainWindow()
{
    delete ui;
}
