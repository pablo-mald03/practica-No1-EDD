#include "jugador.h"
#include"QDebug"

Jugador::Jugador(const std::string _nombre, int _codigo): nombre(_nombre), codigo(_codigo),
    estaObligado(false),tipoObligado(TipoCarta::Predeterminado),
    obligadoSacar(false), colorObligado(TipoColor::PREDETERMINADO)
{
    this->mazo = new ListaEnlazada<Carta>();

}

//Metodo utilizado para odenar las cartas de cada jugador (ordenamiento burbuja normal) O(n cuadrado)
//El metodo se basa en el indice interno de la jerarquia interna de mis cartas
void Jugador::ordenarCartas(bool estaEnFlip){

    int longitudLista = this->mazo->getLongitud();

    if(longitudLista < 2)
        return;

    bool estaOrdenado;

    do {
        estaOrdenado = false;
        Nodo<Carta>* actual = this->mazo->getCabeza();

        for(int i = 0; i < longitudLista - 1; i++) {

            Nodo<Carta>* siguiente = actual->getSiguiente();

            if(menorQue(siguiente->getDato(), actual->getDato(),estaEnFlip)) {

                Carta temp = actual->getDato();
                actual->getDato() = siguiente->getDato();
                siguiente->getDato() = temp;

                estaOrdenado = true;
            }

            actual = siguiente;
        }

    } while(estaOrdenado);

}

//Metodo Fisher–Yates Shuffle (versión clásica con rand) Complejidad O(n)
void Jugador::desordenarCartas(){

    int longitud = this->mazo->getLongitud();

    if(longitud < 2)
        return;

    for(int i = longitud - 1; i > 0; i--){

        int j = rand() % (i + 1);

        if(i != j){

            Carta temp = this->mazo->getValor(i);
            this->mazo->getValor(i) = this->mazo->getValor(j);
            this->mazo->getValor(j) = temp;
        }
    }
}

//Metodo para saber el color que esta obligado a sacar
std::string Jugador::saberColorObligado(TipoColor colorCarta){

    if(!this->obligadoSacar){
        return "CUALQUIERA";
    }

    //(P)
    switch (colorCarta) {
    case TipoColor::AMARILLO:
        return "AMARILLO";
    case TipoColor::VERDE:
        return "VERDE";
    case TipoColor::ROJO:
        return "ROJO";
    case TipoColor::AZUL:
        return "AZUL";
    case TipoColor::NARANJA:
        return "NARANJA";
    case TipoColor::ROSA:
        return "ROSA";
    case TipoColor::VIOLETA:
        return "VIOLETA";
    case TipoColor::TURQUESA:
        return "TURQUESA";
    default:
        return "PREDETERMINADO";
    }

}

//Metodo para definir la prioridad de cartas
int Jugador::prioridadColor(const Carta& carta,bool estaEnFlip) {

    if(!estaEnFlip){

        switch(carta.getAnverso()->getColor().getColorCarta()) {
        case TipoColor::AZUL: return 0;
        case TipoColor::VERDE: return 1;
        case TipoColor::ROJO: return 2;
        case TipoColor::AMARILLO: return 3;
        default: return 4;
        }
    }
    else{

        switch(carta.getReverso()->getColor().getColorCarta()) {
        case TipoColor::NARANJA: return 0;
        case TipoColor::ROSA: return 1;
        case TipoColor::TURQUESA: return 2;
        case TipoColor::VIOLETA: return 3;
        default: return 4;
        }

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
int Jugador::prioridadJerarquia(const Carta& carta,bool estaEnFlip) {
    int indice =0;

    if(!estaEnFlip){
        indice = carta.getAnverso()->getJerarquia();
    }else{
        indice = carta.getReverso()->getJerarquia();
    }
    return indice;
}

//Metodo que permite comparar el menor
bool Jugador::menorQue(const Carta& a, const Carta& b,bool estaEnFlip) {

    int prioridadA = prioridadColor(a,estaEnFlip);
    int prioridadB = prioridadColor(b,estaEnFlip);

    if(prioridadA != prioridadB)
        return prioridadA < prioridadB;

    return prioridadJerarquia(a,estaEnFlip) < prioridadJerarquia(b,estaEnFlip);
}


//=======Metodos que permiten saber si se esta obligado a tirar un color o carta=======
TipoCarta Jugador::getTipoObligado(){
    return this->tipoObligado;
}

bool Jugador::getEstaObligado(){
    return this->estaObligado;
}

void Jugador::setTipoObligado(TipoCarta tipo){
    this->tipoObligado = tipo;
}

void Jugador::setEstaObligado(bool flag){
    this->estaObligado = flag;
}
//=======Fin de los Metodos que permiten saber si se esta obligado a tirar un color o carta=======


//=======Metodos que permiten saber si se esta obligado a tirar un color o carta=======
TipoColor Jugador::getColorObligado(){
    return this->colorObligado;
}

bool Jugador::getObligadoSacar(){
    return this->obligadoSacar;
}

void Jugador::setColorObligado(TipoColor tipo){
    this->colorObligado = tipo;
}

void Jugador::setObligadoSacar(bool flag){
    this->obligadoSacar = flag;
}
//=======Fin de los Metodos que permiten saber si se esta obligado a tirar un color o carta=======



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




