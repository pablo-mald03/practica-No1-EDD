#include "cartadeckui.h"
#include <QPixmap>
#include <QCursor>

CartaDeckUI::CartaDeckUI(int _indice, QString _rutaImg, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), indice(_indice)
{
    QPixmap pix(_rutaImg);
    setPixmap(pix.scaled(140, 197, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setAcceptHoverEvents(true);
    setCursor(Qt::PointingHandCursor);
}

//Destructor
CartaDeckUI::~CartaDeckUI(){

}

//Evento que detecta cuando se ha hecho click sobre la carta
void CartaDeckUI::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit cartaClickeda(this->indice);
}

//Evento que detecta cuando el cursor esta sobre la carta
void CartaDeckUI::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setY(y() - 25);
}

//Evento que detecta cuando el cursor deja de estar sobre la carta (Regresa a su lugar)
void CartaDeckUI::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setY(y() + 25);
}
