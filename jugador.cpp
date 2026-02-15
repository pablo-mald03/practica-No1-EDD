#include "jugador.h"
#include"QDebug"

Jugador::Jugador(const std::string _nombre, int _codigo): nombre(_nombre), codigo(_codigo)
{
    this->mazo = new ListaEnlazada<Carta>();

}

//Metodo utilizado para odenar las cartas de cada jugador (ordenamiento burbuja normal) O(n cuadrado)
//El metodo se basa en el indice interno de la jerarquia interna de mis cartas
void Jugador::ordenarCartas(){

    int longitudLista = this->mazo->getLongitud();

    if(longitudLista < 2)
        return;

    bool estaOrdenado;

    do {
        estaOrdenado = false;
        Nodo<Carta>* actual = this->mazo->getCabeza();

        for(int i = 0; i < longitudLista - 1; i++) {

            Nodo<Carta>* siguiente = actual->getSiguiente();

            if(menorQue(siguiente->getDato(), actual->getDato())) {

                Carta temp = actual->getDato();
                actual->getDato() = siguiente->getDato();
                siguiente->getDato() = temp;

                estaOrdenado = true;
            }

            actual = siguiente;
        }

    } while(estaOrdenado);

}

//Metodo para definir la prioridad de cartas
int Jugador::prioridadColor(const Carta& carta) {

    switch(carta.getAnverso()->getColor().getColorCarta()) {
    case TipoColor::AZUL: return 0;
    case TipoColor::VERDE: return 1;
    case TipoColor::ROJO: return 2;
    case TipoColor::AMARILLO: return 3;
    default: return 4;
    }
}

//Metodo que retorna la pripridad de jerarquia interna que tienen las cartas (propia logica)
// 0-9 → numericas = CLARO
// 10 → bloqueo = CLARO
// 11 → cambio direccion = CLARO
// 12 → +2 | +1 = CLARO
//13 -> suma multicolor = CLARO
//14 -> comodin multicolor = CLARO
//15 -> eclipse = CLARO (P)
//16 -> espia = CLARO (P)
int Jugador::prioridadJerarquia(const Carta& carta) {
    int indice = carta.getIndice();
    return indice;
}

//Metodo que permite comparar el menor
bool Jugador::menorQue(const Carta& a, const Carta& b) {

    int prioridadA = prioridadColor(a);
    int prioridadB = prioridadColor(b);

    if(prioridadA != prioridadB)
        return prioridadA < prioridadB;

    return prioridadJerarquia(a) < prioridadJerarquia(b);
}


//Apartado de acciones que puede hacer el jugador


//Sobrecarga del operador igual
bool Jugador::operator==(const Jugador& otro) const{
    return this->nombre == otro.nombre && this->codigo == otro.codigo;
}

//Metodos getters y setters
int Jugador::getCodigo()const{
    return this->codigo + 1;
}

int Jugador::getIndice()const{
    return this->codigo;
}


std::string Jugador::getNombre()const{
    return this->nombre;
}

//Metodo que permite obtener el mazo del jugador
ListaEnlazada<Carta> * Jugador::getMazo(){
    return this->mazo;
}


//Destructor del objeto
Jugador::~Jugador(){
    delete this->mazo;
}




