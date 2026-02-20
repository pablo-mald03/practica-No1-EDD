#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

#include"nodo.h"

template<typename T>
class ListaCircular
{

private:
    Nodo<T> * cabeza;
    //Nodo que permite ir recorriendo en sentido circular la lista
    Nodo<T> * actualTurno;
    int longitud;

    //Metodo de busqueda de nodo
    Nodo<T> * buscarNodo(int posicion) const;

public:
    ListaCircular();
    ~ListaCircular();

    //Metodos para el uso de la lista circular
    bool esVacia()const;
    int getLongitud()const;

    void insertar(const T& valor);

    void eliminarEn(int indice);

    //Metodos que sirven para saltar posiciones sin retornar nada
    void avanzar();
    void retroceder();

    //Metodo que permite saber el jugador actual para iniciar partida
    T& getActual();

    //Metodos de pick para echar vistazos al siguiente y al anterior
    T& pickSiguiente();
    T& pickAnterior();

    //Metodo para dar vuelta (integracion directa)
    T& obtenerEn(int indice);

};

#endif // LISTACIRCULAR_H
