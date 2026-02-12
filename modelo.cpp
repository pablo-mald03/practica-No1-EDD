#include "modelo.h"

Modelo::Modelo(const ColorCarta&_colorRef, const std::string &_nombre, const std::string &_lado, TipoCarta _tipo)
    : color(_colorRef),nombre(_nombre),lado(_lado), tipo(_tipo)
{

}

//Metodos getter y setter
void Modelo::setColor(const ColorCarta &_color){
    this->color = _color;
}
void Modelo::setNombre(const std::string &_nombre){
    this->nombre = _nombre;
}
void Modelo::setLado(const std::string &_lado){
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

//Sobrecarga de operador ==

bool Modelo::operator==(const Modelo& otro) const {
    return this->nombre == otro.nombre && this->lado== otro.lado && this->tipo == otro.tipo &&
        this->color == otro.color;
}


Modelo::~Modelo(){

}
