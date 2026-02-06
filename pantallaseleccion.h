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

private slots:
    void on_btnRegreso_clicked();
};

#endif // PANTALLASELECCION_H
