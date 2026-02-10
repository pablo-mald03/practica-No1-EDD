#include "modelo.h"

Modelo::Modelo(const ColorCarta&_colorRef, const std::string &_nombre, const std::string &_lado)
    : color(_colorRef),nombre(_nombre),lado(_lado)
{

}

//Metodos getter y setter
void Modelo::setColor(const ColorCarta &_color){
    this->color = _color;
}
void Modelo::setNombre(std::string _nombre){
    this->nombre = _nombre;
}
void Modelo::setLado(std::string _lado){
    this->lado = _lado;
}
std::string Modelo::getNombre()const{
    return this->nombre;
}
ColorCarta Modelo::getColor()const{
    return this->color;
}
std::string Modelo::getLado()const{
    return this->lado;
}


Modelo::~Modelo(){

}
