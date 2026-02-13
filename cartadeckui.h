#ifndef CARTADECKUI_H
#define CARTADECKUI_H

#include <QObject>
#include <QGraphicsPixmapItem>

class CartaDeckUI: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    int indice;

public:
    // idBackend para que sepas qué nodo de tu lista enlazada es
    CartaDeckUI(int _idCarta, QString _rutaImg, QGraphicsItem *parent = nullptr);
    ~CartaDeckUI();

signals:
    void cartaClickeda(int _indice);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;


};

#endif // CARTADECKUI_H
