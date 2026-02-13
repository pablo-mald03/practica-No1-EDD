#ifndef CARTA_H
#define CARTA_H
#include"modelo.h"

class Carta
{

private:
    Modelo* reverso;
    Modelo* anverso;
    int indice;

public:
    Carta(Modelo *_reverso,  Modelo * _anverso,int _indice);
    ~Carta() = default;

    //Metodos getters
    Modelo& getReverso() const;
    Modelo& getAnverso() const;
    int getIndice()const;

};

#endif // CARTA_H
