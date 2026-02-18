#include "modelo.h"

Modelo::Modelo(const ColorCarta&_colorRef, const std::string &_nombre, const std::string &_lado, TipoCarta _tipo, int _jerarquia)
    : color(_colorRef),nombre(_nombre),lado(_lado), tipo(_tipo), jerarquia(_jerarquia)
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
ColorCarta Modelo::getColor() const{
    return this->color;
}
std::string Modelo::getLado()const{
    return this->lado;
}

TipoCarta Modelo::getTipo()const{
    return this->tipo;
}

int Modelo::getJerarquia()const{
    return this->jerarquia;
}

//Metodo que devuelve el reverso
std::string Modelo::getReversoModelo()const{
    return ":/assets/mediaGame/ReversoCarta.png";
}

Modelo::~Modelo(){

}
