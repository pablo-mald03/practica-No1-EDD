#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include"nodo.h"


template<typename T>
class ListaEnlazada
{

private:
    Nodo<T> * cabeza;
    Nodo<T> * cola;
    int longitud;
public:
    ListaEnlazada();
    ~ListaEnlazada();

    //Metodos para usar la lista
    void insertarAtras(const T&valor);
    void insertarFrente (const T&valor);

    void removerAtras();
    void removerFrente();

    bool esVacia() const;
    int getLongitud()const;

    void limpiar();

    //METODOS ESPECIALES QUE PERMITEN MOVERSE POR LA LISTA COMO SE DESEE
    void insertar(int pos, const T& valor);
    void eliminar(int pos);

    T& getValor(int pos);
    const T& verValor(int indice) const;

    int buscarIndice(const T& valor) const;

private:
    //Metodo especial para hallar los nodos
     Nodo<T>* getNodo(int pos) const;

};

#endif // LISTAENLAZADA_H
