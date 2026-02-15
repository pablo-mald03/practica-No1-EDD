#include "carta.h"

Carta::Carta(Modelo *_reverso,  Modelo * _anverso,int _indice)
    :reverso(_reverso), anverso(_anverso), indice(_indice)
{
}

//Constructor vacio
Carta::Carta() : reverso(nullptr), anverso(nullptr), indice(0)
{

}


//Metodo que permite retornar el reverso de la carta
Modelo* Carta::getReverso()const{
    return this->reverso;
}
//Metodo que permite retornar el anverso de la carta
Modelo* Carta::getAnverso()const{
    return this->anverso;
}
//Metodo que permite obtener el indice de la carta
int Carta::getIndice()const{
    return this->indice;
}
