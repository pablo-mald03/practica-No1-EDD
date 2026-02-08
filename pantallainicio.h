#ifndef PANTALLAINICIO_H
#define PANTALLAINICIO_H

#include <QWidget>
#include<QApplication>

namespace Ui {
class PantallaInicio;
}

class PantallaInicio : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaInicio(QWidget *parent = nullptr);
    ~PantallaInicio();

signals:
    void solicitarSeleccion();

private slots:
    void on_pushButton_2_clicked();

    void on_btnInicio_clicked();

private:
    Ui::PantallaInicio *ui;
};

#endif // PANTALLAINICIO_H
