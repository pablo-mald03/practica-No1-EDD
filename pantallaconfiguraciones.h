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
    explicit PantallaConfiguraciones(bool &flag, DatosConfiguracion * &config,QWidget *parent = nullptr);
    ~PantallaConfiguraciones();

    //Metodo que permite setear las opciones por defecto
    void setChekedOpciones(DatosConfiguracion * &config, bool & flag);

private:
    Ui::PantallaConfiguraciones *ui;

    DatosConfiguracion * a_config = nullptr;

signals:
    void solicitarRegresoModalidad();
private slots:
    void on_btnRetorno_clicked();
    void on_checkRobo_toggled(bool checked);
    void on_checkGrito_toggled(bool checked);
    void on_checkGanarNegra_toggled(bool checked);
    void on_checkBoxFlip_toggled(bool checked);
};

#endif // PANTALLACONFIGURACIONES_H
