#ifndef PILA_H
#define PILA_H

#include"nodo.h"

template<typename T>
class Pila
{
private:
    Nodo<T> * cima;
    int longitud;

public:

    Pila();
    ~Pila();

    int getLongitud() const;
    bool estaVacia() const;
    void push(const T& valor);
    void pop();
    T& verTop();
};

#endif // PILA_H
