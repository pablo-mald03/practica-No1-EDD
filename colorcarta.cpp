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


ColorCarta::~ColorCarta(){

}
