#ifndef PANTALLACONFIGURACIONES_H
#define PANTALLACONFIGURACIONES_H

#include <QWidget>
struct DatosConfiguracion;

namespace Ui {
class PantallaConfiguraciones;
}

class PantallaConfiguraciones : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaConfiguraciones(DatosConfiguracion * &config,QWidget *parent = nullptr);
    ~PantallaConfiguraciones();

    //Metodo que permite setear las opciones por defecto
    void setChekedOpciones(DatosConfiguracion * &config);

private:
    Ui::PantallaConfiguraciones *ui;

    DatosConfiguracion * a_config;

signals:
    void solicitarRegresoModalidad();
private slots:
    void on_btnRetorno_clicked();
};

#endif // PANTALLACONFIGURACIONES_H
