#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//Region de importacion de ui
#include"pantallainicio.h"
#include"pantallaseleccion.h"
#include"pantallamodalidad.h"

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

    //Enrutamientos
    PantallaInicio *inicio = nullptr;
    PantallaSeleccion * pantallaSelect = nullptr;
    PantallaModalidad * pantallaModal = nullptr;

    //Metodos de signals de hijos
    void mostrarSeleccion();
    void mostrarModalidad(int cantidadPersonas, bool personalizacion);

};
#endif // MAINWINDOW_H
