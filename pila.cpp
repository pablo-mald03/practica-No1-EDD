#include "pila.h"
#include <stdexcept>
#include"carta.h"

//instancia posible de pila
template class Pila<Carta>;

template<typename T>
Pila<T>::Pila() : cima(nullptr), longitud(0) {}

//Metodo para destruir lo que este en la pila
template<typename T>
Pila<T>::~Pila() {
    while (!estaVacia()) {
        pop();
    }
}

//Metodo para saber si esta vacia
template<typename T>
bool Pila<T>::estaVacia() const {
    return cima == nullptr;
}

//Metodo para saber la longitud de la pila
template<typename T>
int Pila<T>::getLongitud() const {
    return longitud;
}

//Metodo que sirve para agregar un objeto hasta arriba de la pila
template<typename T>
void Pila<T>::push(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor);
    nuevo->setSiguiente(cima);

    if (cima != nullptr) {
        cima->setAnterior(nuevo);
    }

    cima = nuevo;
    longitud++;
}

//Metodo para sacar algo de la pila
template<typename T>
void Pila<T>::pop() {
    if (estaVacia())
        throw std::runtime_error("La pila esta vacia");

    Nodo<T>* temp = cima;
    cima = cima->getSiguiente();

    if (cima != nullptr) {
        cima->setAnterior(nullptr);
    }

    delete temp;
    longitud--;
}

//Metodo para darle un vistazo a la pila
template<typename T>
T& Pila<T>::verTop() {
    if (estaVacia())
        throw std::runtime_error("La pila vacia");

    return cima->getDato();
}
