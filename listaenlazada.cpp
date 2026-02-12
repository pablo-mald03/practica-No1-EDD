#include"listaenlazada.h"
#include <stdexcept>
#include"carta.h"

//instancia posible de nodo
template class ListaEnlazada<Carta*>;

template<typename T>
ListaEnlazada<T>::ListaEnlazada(): cabeza(nullptr),cola(nullptr), longitud(0)
{

}

template<typename T>
ListaEnlazada<T>::~ListaEnlazada()
{
    limpiar();
}

//Metodo que retorna si la lista esta vacia
template<typename T>
bool ListaEnlazada<T>::esVacia() const{
    return this->cabeza == nullptr;
}

//Metodo que retorna la longitud de la lista
template<typename T>
int ListaEnlazada<T>::getLongitud() const
{
    return this->longitud;
}


//Metodo que agrega al frente de la lista
template<typename T>
void ListaEnlazada<T>::insertarAtras(const T& valor)
{
    Nodo<T>* nuevo = new Nodo<T>(valor);

    if (esVacia())
    {
        this->cabeza = cola = nuevo;
    }
    else
    {
        this->cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        this->cola = nuevo;
    }

    this->longitud++;
}

//Metodo para insertar al frente de la lista
template<typename T>
void ListaEnlazada<T>::insertarFrente(const T& valor){

    Nodo<T>* nuevo = new Nodo<T>(valor);

    if (esVacia())
    {
        this->cabeza = cola = nuevo;
    }
    else
    {
        nuevo->setSiguiente(cabeza);
        this->cabeza->setAnterior(nuevo);
        this->cabeza = nuevo;
    }

    this->longitud++;
}

//Metodo para remover atras de la lista
template<typename T>
void ListaEnlazada<T>::removerAtras()
{
    if (esVacia()){
        return;
    }

    Nodo<T>* temp = this->cola;

    if (this->cabeza == this->cola)
    {
        this->cabeza = this->cola = nullptr;
    }
    else
    {
        this->cola = this->cola->getAnterior();
        this->cola->setSiguiente(nullptr);
    }

    delete temp;
    this->longitud--;
}

//Metodo para remover al frente
template<typename T>
void ListaEnlazada<T>::removerFrente()
{
    if (esVacia()) return;

    Nodo<T>* temp = this->cabeza;

    if (this->cabeza == cola)
    {
        this->cabeza = cola = nullptr;
    }
    else
    {
        this->cabeza = this->cabeza->getSiguiente();
        this->cabeza->setAnterior(nullptr);
    }

    delete temp;
    this->longitud--;
}

//====================REGION DE METODOS ESPECIALES DE LA LISTA=================================
//Metodo privado de la clase (Busca nodos) por busqueda secuencial con modificacion O(n)
template<typename T>
Nodo<T>* ListaEnlazada<T>::getNodo(int indice) const{

    if(indice>=longitud){
        throw std::out_of_range("Indice fuera de rango de la lista enlazada");
    }

    Nodo<T>* actual;

    if (indice < this->longitud / 2)
    {
        actual = this->cabeza;
        for (int i = 0; i < indice; i++)
        {
            actual = actual->getSiguiente();
        }
    }
    else
    {
        actual = cola;
        for (int i = this->longitud - 1; i > indice; i--){
           actual = actual->getAnterior();
        }
    }
    return actual;
}

//Metodo que sirve para insertar en cualquier indice
template<typename T>
void ListaEnlazada<T>::insertar(int indice, const T& valor)
{
    if (indice > this->longitud){
        throw std::out_of_range("Indice fuera de rango de la lista enlazada");
    }

    if (indice == 0)
    {
        insertarFrente(valor);
        return;
    }

    if (indice == this->longitud)
    {
        insertarAtras(valor);
        return;
    }

    Nodo<T>* actual = getNodo(indice);
    Nodo<T>* anterior = actual->getAnterior();

    Nodo<T>* nuevo = new Nodo<T>(valor);

    nuevo->setSiguiente(actual);
    nuevo->setAnterior(anterior);

    anterior->setSiguiente(nuevo);
    actual->setAnterior(nuevo);

    this->longitud++;
}

//Metodo que sirve para eliminar un dato EN CUALQUIER POSICION
template<typename T>
void ListaEnlazada<T>::eliminar(int indice)
{
    if (indice >= this->longitud){
       throw std::out_of_range("Indice fuera de rango de la lista enlazada");
    }

    if (indice == 0)
    {
        removerFrente();
        return;
    }

    if (indice == this->longitud - 1)
    {
        removerAtras();
        return;
    }

    Nodo<T>* actual = getNodo(indice);
    Nodo<T>* anterior = actual->getAnterior();
    Nodo<T>* siguiente = actual->getSiguiente();

    anterior->setSiguiente(siguiente);
    siguiente->setAnterior(anterior);

    delete actual;
    this->longitud--;
}

//Metodo que permite obtener un valor por posicion
template<typename T>
T& ListaEnlazada<T>::getValor(int indice)
{
    return getNodo(indice)->getDato();
}

//Metodo que permite obtener un valor CONSTANTE. Es decir que se solo se echa un vistazo al nodo
template<typename T>
const T& ListaEnlazada<T>::verValor(int indice) const
{
    return getNodo(indice)->getDato();
}

//Metodo que sirve para buscar el indice donde esta ubicado un nodo
template<typename T>
int ListaEnlazada<T>::buscarIndice(const T& valor) const
{
    Nodo<T>* actual = cabeza;
    int indice = 0;

    while (actual != nullptr)
    {
        if (actual->getDato() == valor){
             return indice;
        }

        actual = actual->getSiguiente();
        indice++;
    }
    //retorna -1 si no existe
    return -1;
}


//====================FIN DE LA REGION DE METODOS ESPECIALES DE LA LISTA=================================

template<typename T>
void ListaEnlazada<T>::limpiar()
{
    while (!esVacia())
        removerFrente();
}







