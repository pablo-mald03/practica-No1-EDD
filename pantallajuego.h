#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <QWidget>

//Include de la partida (INTEGRACION DE BACKEND)
#include"partida.h"

struct DatosConfiguracion;
namespace Ui {
class PantallaJuego;
}

class PantallaJuego : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaJuego(bool &estaConfigurando, DatosConfiguracion * &config,QWidget *parent = nullptr);
    ~PantallaJuego();

private:
    Ui::PantallaJuego *ui;

    Partida * partida = nullptr;

signals:
    void solicitarSalida();
private slots:
    void on_btnRetorno_clicked();
};

#endif // PANTALLAJUEGO_H
