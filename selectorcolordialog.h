#ifndef SELECTORCOLORDIALOG_H
#define SELECTORCOLORDIALOG_H

#include <QDialog>

namespace Ui {
class SelectorColorDialog;
}

class SelectorColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectorColorDialog(bool _estaFlip,QWidget *parent = nullptr);
    ~SelectorColorDialog();

    //Metodo para aplicar estilos
    void aplicarEstilos();
    void configurarColores(bool estaFlip);
    int getColorElegido() const;

private slots:
    void on_btnColor1_clicked();

    void on_btnColor2_clicked();

    void on_btnColor3_clicked();

    void on_btnColor4_clicked();

private:
    Ui::SelectorColorDialog *ui;

    bool estaFlip;
    int colorElegido;
};

#endif // SELECTORCOLORDIALOG_H
