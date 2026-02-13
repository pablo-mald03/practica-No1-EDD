#include "carta.h"

Carta::Carta(const Modelo &_reverso, const Modelo &_anverso,int _indice)
    :reverso(_reverso), anverso(_anverso), indice(_indice)
{

}

Carta::~Carta(){

}

//Metodo que permite retornar el reverso de la carta
Modelo& Carta::getReverso(){
    return this->reverso;
}
//Metodo que permite retornar el anverso de la carta
Modelo& Carta::getAnverso(){
    return this->anverso;
}
//Metodo que permite obtener el indice de la carta
int Carta::getIndice()const{
    return this->indice;
}
