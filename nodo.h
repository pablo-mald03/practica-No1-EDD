#ifndef NODO_H
#define NODO_H

template<typename T>
class Nodo
{

private:
    T dato;
    Nodo<T> * siguiente;
    Nodo<T> * anterior;

public:
    Nodo(const T&valor);

    T getDato()const;

    /*Metodos getters y setters para reutilizar nodo*/
    Nodo<T>* getSiguiente() const;
    Nodo<T>* getAnterior() const;

    void setSiguiente(Nodo<T>* sig);
    void setAnterior(Nodo<T>* ant);

};

#endif // NODO_H
