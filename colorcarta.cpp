#include "colorcarta.h"

ColorCarta::ColorCarta(const std::string &_color):color(_color)
{

}

//Metodos getter y setter
void ColorCarta::setColor(const std::string &_color){
    this->color = _color;
}

std::string ColorCarta::getColor(){
    return this->color;
}

//sobrecarga de operador ==
bool ColorCarta::operator==(const ColorCarta& otro) const{
    return this->color == otro.color;
}

ColorCarta::~ColorCarta(){

}
