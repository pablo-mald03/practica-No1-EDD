#ifndef PANTALLAMODALIDAD_H
#define PANTALLAMODALIDAD_H

#include <QWidget>
struct DatosConfiguracion;

namespace Ui {
class PantallaModalidad;
}

class PantallaModalidad : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaModalidad(DatosConfiguracion * &config, int cantidadPersonas, bool personalizacion, QWidget *parent = nullptr);
    ~PantallaModalidad();

    //Metodos para setear valores
    void setCantidad(int valor);
    void setPersonalizacion(bool flag);

    //Metodo que se encarga de actualizar los datos en UI
    void setSeleccion();

    //Metodos que permiten activar/desctivar los checkboxes
    void setChekedOpciones(DatosConfiguracion * &config);

private:
    Ui::PantallaModalidad *ui;

    //Apartado de atributos de la clase propios
    int cantidad;
    bool personalizado;

    DatosConfiguracion * m_config;


signals:
    void solicitarRegresoSeleccion();
    void solicitarConfiguraciones();

private slots:
    void on_btnRetorno_clicked();

    void on_checkStacking_toggled(bool checked);
    void on_checkMas4_toggled(bool checked);
    void on_btnAvanzada_clicked();
};

#endif // PANTALLAMODALIDAD_H
