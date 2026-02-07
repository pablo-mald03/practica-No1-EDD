#ifndef PANTALLACONFIGURACIONES_H
#define PANTALLACONFIGURACIONES_H

#include <QWidget>

namespace Ui {
class PantallaConfiguraciones;
}

class PantallaConfiguraciones : public QWidget
{
    Q_OBJECT

public:
    explicit PantallaConfiguraciones(QWidget *parent = nullptr);
    ~PantallaConfiguraciones();

private:
    Ui::PantallaConfiguraciones *ui;
};

#endif // PANTALLACONFIGURACIONES_H
