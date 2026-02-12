#include"listacircular.h"
#include"jugador.h"
#include <stdexcept>

//instancia posible de nodo
template class ListaCircular<Jugador*>;


template<typename T>
ListaCircular<T>::ListaCircular()
    :cabeza(nullptr), actualTurno(nullptr),longitud(0)
{

}
template<typename T>
int ListaCircular<T>::getLongitud()const{
    return this->longitud;
}

//Metodo para saber si esta vacia
template<typename T>
bool ListaCircular<T>::esVacia() const{
    return this->cabeza == nullptr;
}

//Metodo que sirve para buscar un nodo en una posicion
template<typename T>
Nodo<T> * ListaCircular<T>::buscarNodo(int indice) const{

    if(indice < 0||indice >= this->longitud){
        throw std::out_of_range("Posicion fuera de los limites de la lista");
    }

    Nodo<T>* actual = cabeza;

    if(indice <this->longitud / 2){

        for(int i = 0;i <indice;i++){
            actual = actual->getSiguiente();
        }
    }
    else{
        actual = cabeza->getAnterior();
        for (int i = this->longitud - 1; i > indice; i--){
            actual = actual->getAnterior();
        }
    }

    return actual;
}

//metodo que permite insertar al final. Es el caso base que se seguira en todo el juego
template<typename T>
void ListaCircular<T>::insertar(const T&valor){
    Nodo<T>* nuevo = new Nodo<T>(valor);

    if (esVacia()) {
        cabeza = nuevo;
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        this->actualTurno = nuevo;
    }
    else {
        Nodo<T>* ultimo = cabeza->getAnterior();

        nuevo->setSiguiente(cabeza);
        nuevo->setAnterior(ultimo);

        ultimo->setSiguiente(nuevo);
        cabeza->setAnterior(nuevo);
    }

    this->longitud++;
}

//Metodo que permite eliminar en cualquier lugar
template<typename T>
void ListaCircular<T>::eliminarEn(int indice)
{
    if (esVacia()){
        throw std::runtime_error("Lista vacía");
    }

    Nodo<T>* nodoEliminar = buscarNodo(indice);

    if (this->longitud == 1) {
        delete nodoEliminar;
        cabeza = nullptr;
    }
    else {
        Nodo<T>* anterior = nodoEliminar->getAnterior();
        Nodo<T>* siguiente = nodoEliminar->getSiguiente();

        anterior->setSiguiente(siguiente);
        siguiente->setAnterior(anterior);

        if (indice == 0){
            cabeza = siguiente;
        }

        delete nodoEliminar;
    }

    this->longitud--;
}

//Metodo que permite mover la lista circular hacia adelante sin necesidad de retorno (Util para aleatoriedad)
template<typename T>
void ListaCircular<T>::avanzar()
{
    if (esVacia())
        throw std::runtime_error("Lista vacía");

    actualTurno = actualTurno->getSiguiente();
}

//Metodo que permite mover la lista circular hacia atras sin necesidad de retorno (Util para aleatoriedad)
template<typename T>
void ListaCircular<T>::retroceder()
{
    if (esVacia())
        throw std::runtime_error("Lista vacía");

    actualTurno = actualTurno->getAnterior();
}

//Metodo que permite obtener el actual (UTIL MAYORMENTE AL INICIAR PARTIDA)
template<typename T>
T& ListaCircular<T>::getActual()
{
    if (esVacia())
        throw std::runtime_error("Lista vacía");

    return actualTurno->getDato();
}


//Destructor de todos los nodos
template<typename T>
ListaCircular<T>::~ListaCircular()
{
    if (esVacia())
        return;

    Nodo<T>* actual = cabeza->getSiguiente();

    while (actual != cabeza)
    {
        Nodo<T>* temp = actual;
        actual = actual->getSiguiente();

        delete temp->getDato();
        delete temp;
    }

    delete cabeza->getDato();
    delete cabeza;

    cabeza = nullptr;
}

