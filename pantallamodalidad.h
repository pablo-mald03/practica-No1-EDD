#ifndef PANTALLAMODALIDAD_H
#define PANTALLAMODALIDAD_H

#include <QWidget>

namespace Ui {
class PantallaModalidad;
}

class PantallaModalidad : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaModalidad(int cantidadPersonas, bool personalizacion, QWidget *parent = nullptr);
    ~PantallaModalidad();

private:
    Ui::PantallaModalidad *ui;

    //Apartado de atributos de la clase propios
    int cantidad;
    bool personalizado;


signals:
    void solicitarRegresoSeleccion();

private slots:
    void on_btnRetorno_clicked();

};

#endif // PANTALLAMODALIDAD_H
