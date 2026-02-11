#include "nodo.h"

template<typename T>
Nodo<T>::Nodo(const T &valor): dato(valor), siguiente(nullptr), anterior(nullptr)
{

}

template<typename T>
T Nodo<T>::getDato() const{
    return dato;
}


/*Metodos getters y setters para reutilizar nodo*/
template<typename T>
Nodo<T>* Nodo<T>::getSiguiente() const{
    return this->siguiente;
}
template<typename T>
Nodo<T>* Nodo<T>::getAnterior() const{
    return this->anterior;
}

template<typename T>
void Nodo<T>::setSiguiente(Nodo<T>* sig){
    this->siguiente = sig;
}
template<typename T>
void Nodo<T>::setAnterior(Nodo<T>* ant){
    this->siguiente = ant;
}
