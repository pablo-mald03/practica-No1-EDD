#include "colorcarta.h"

ColorCarta::ColorCarta(const TipoColor &_color):color(_color)
{

}

//Metodos getter y setter
void ColorCarta::setColor(const TipoColor &_color){
    this->color = _color;
}

TipoColor ColorCarta::getColorCarta(){
    return this->color;
}

//sobrecarga de operador ==
bool ColorCarta::operator==(const ColorCarta& otro) const{
    return this->color == otro.color;
}

ColorCarta::~ColorCarta(){

}
