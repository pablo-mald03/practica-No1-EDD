#ifndef PANTALLASELECCION_H
#define PANTALLASELECCION_H

#include <QWidget>

namespace Ui {
class PantallaSeleccion;
}

class PantallaSeleccion : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaSeleccion(QWidget *parent = nullptr);
    ~PantallaSeleccion();

private:
    Ui::PantallaSeleccion *ui;

signals:
    void solicitarRegresoInicio();
    void solicitarModalidad(int cantidadPersonas, bool personalizacion);

private slots:
    void on_btnRegreso_clicked();
    void on_btnDosJugadores_clicked();
    void on_btnTresJugadores_clicked();
    void on_btnCuatroJugadores_clicked();
    void on_btnMasJugadores_clicked();
};

#endif // PANTALLASELECCION_H
