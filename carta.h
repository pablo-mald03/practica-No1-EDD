#ifndef CARTA_H
#define CARTA_H
#include"modelo.h"

class Carta
{

private:
    Modelo reverso;
    Modelo anverso;
    int indice;

public:
    Carta(const Modelo &_reverso, const Modelo &_anverso,int _indice);
    ~Carta();

    //Metodos getters
    Modelo& getReverso();
    Modelo& getAnverso();
    int getIndice()const;

};

#endif // CARTA_H
