#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//Region de importacion de ui
#include"pantallainicio.h"
#include"pantallaseleccion.h"
#include"pantallamodalidad.h"
#include"pantallaconfiguraciones.h"
#include"pantallaconfiguraciones.h"


struct DatosConfiguracion {
    bool stacking;
    bool retoMas4;
    bool modoRobo;
    bool gritoUno;
    bool ganarNegra;
    bool flip;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //Variables necesarias para utilizar
    bool estaConfigurando;


    //Enrutamientos
    PantallaInicio *inicio = nullptr;
    PantallaSeleccion * pantallaSelect = nullptr;
    PantallaModalidad * pantallaModal = nullptr;
    PantallaConfiguraciones * pantallaConfiguracion = nullptr;
    //Punteros de configuracion
    DatosConfiguracion * datosConfig = nullptr;

    //Metodos de signals de hijos
    void mostrarSeleccion();
    void mostrarModalidad(int cantidadPersonas, bool personalizacion);
    void mostrarConfiguraciones();
    void mostrarJuego();

    //VaciarPunteroDatos
    void vaciarPunteroDatos();
};
#endif // MAINWINDOW_H
