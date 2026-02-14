#include "numerica.h"

Numerica::Numerica(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::CartaNumerica),valor(_valor)
{}

//Metodos getters y setters
int Numerica::getValor()const {
    return this->valor;
}

void Numerica::setValor(int _valor){
     this->valor = _valor;
}

//Metodo que retorna el valor de imagen de la carta
std::string Numerica::getPathImagen() const{

    if(Modelo::getLado() == "claro"){

        if(Modelo::getColor().getColorCarta() == TipoColor::AMARILLO){
            return this->getDirectoriosAmarillo();
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROJO){
            return this->getDirectoriosRojo();
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::VERDE){
            return this->getDirectoriosVerde();
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::AZUL){
            return this->getDirectoriosAzul();
        }

    }else if(Modelo::getLado() == "oscuro"){

        if(Modelo::getColor().getColorCarta() == TipoColor::VIOLETA){

            return this->getDirectoriosVioleta();
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROSA){
            return this->getDirectoriosRosa();
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::NARANJA){
            return this->getDirectoriosNaranja();
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::TURQUESA){
            return this->getDirectoriosTurquesa();
        }
    }

    return ":/assets/mediaGame/ReversoCarta.png";
}


//=========APARTADO DE METODOS QUE PERMITEN RETORNAR EL COLOR EN BASE AL NUMERO========

//Retorna los directorios de las cartas rosas
std::string Numerica::getDirectoriosRosa()const{

    switch(this->valor){
    case 0:
        return ":/assets/mediaGame/CartaRO0.png";
    case 1:
        return ":/assets/mediaGame/CartaRO1.png";
    case 2:
        return ":/assets/mediaGame/CartaRO2.png";
    case 3:
        return ":/assets/mediaGame/CartaRO3.png";
    case 4:
        return ":/assets/mediaGame/CartaRO4.png";
    case 5:
        return ":/assets/mediaGame/CartaRO5.png";
    case 6:
        return ":/assets/mediaGame/CartaRO6.png";
    case 7:
        return ":/assets/mediaGame/CartaRO7.png";
    case 8:
        return ":/assets/mediaGame/CartaRO8.png";
    case 9:
        return ":/assets/mediaGame/CartaRO9.png";

    default:
        return ":/assets/mediaGame/ReversoCarta.png";

    }
}
//Retorna los directorios de las cartas violetas
std::string Numerica::getDirectoriosVioleta()const{
    switch(this->valor){
    case 0:
        return ":/assets/mediaGame/CartaVI0.png";
    case 1:
        return ":/assets/mediaGame/CartaVI1.png";
    case 2:
        return ":/assets/mediaGame/CartaVI2.png";
    case 3:
        return ":/assets/mediaGame/CartaVI3.png";
    case 4:
        return ":/assets/mediaGame/CartaVI4.png";
    case 5:
        return ":/assets/mediaGame/CartaVI5.png";
    case 6:
        return ":/assets/mediaGame/CartaVI6.png";
    case 7:
        return ":/assets/mediaGame/CartaVI7.png";
    case 8:
        return ":/assets/mediaGame/CartaVI8.png";
    case 9:
        return ":/assets/mediaGame/CartaVI9.png";

    default:
        return ":/assets/mediaGame/ReversoCarta.png";
    }
}
//Retorna los directorios de las cartas turquesas
std::string Numerica::getDirectoriosTurquesa()const{
    switch(this->valor){
    case 0:
        return ":/assets/mediaGame/CartaT0.png";
    case 1:
        return ":/assets/mediaGame/CartaT1.png";
    case 2:
        return ":/assets/mediaGame/CartaT2.png";
    case 3:
        return ":/assets/mediaGame/CartaT3.png";
    case 4:
        return ":/assets/mediaGame/CartaT4.png";
    case 5:
        return ":/assets/mediaGame/CartaT5.png";
    case 6:
        return ":/assets/mediaGame/CartaT6.png";
    case 7:
        return ":/assets/mediaGame/CartaT7.png";
    case 8:
        return ":/assets/mediaGame/CartaT8.png";
    case 9:
        return ":/assets/mediaGame/CartaT9.png";

    default:
        return ":/assets/mediaGame/ReversoCarta.png";
    }
}
//Retorna los directorios de las cartas naranjas
std::string Numerica::getDirectoriosNaranja()const{
    switch(this->valor){
    case 0:
        return ":/assets/mediaGame/CartaN0.png";
    case 1:
        return ":/assets/mediaGame/CartaN1.png";
    case 2:
        return ":/assets/mediaGame/CartaN2.png";
    case 3:
        return ":/assets/mediaGame/CartaN3.png";
    case 4:
        return ":/assets/mediaGame/CartaN4.png";
    case 5:
        return ":/assets/mediaGame/CartaN5.png";
    case 6:
        return ":/assets/mediaGame/CartaN6.png";
    case 7:
        return ":/assets/mediaGame/CartaN7.png";
    case 8:
        return ":/assets/mediaGame/CartaN8.png";
    case 9:
        return ":/assets/mediaGame/CartaN9.png";
    default:
        return ":/assets/mediaGame/ReversoCarta.png";

    }
}
//Retorna los directorios de las cartas rojas
std::string Numerica::getDirectoriosRojo()const{
    switch(this->valor){
    case 0:
        return ":/assets/mediaGame/CartaR0.png";
    case 1:
        return ":/assets/mediaGame/CartaR1.png";
    case 2:
        return ":/assets/mediaGame/CartaR2.png";
    case 3:
        return ":/assets/mediaGame/CartaR3.png";
    case 4:
        return ":/assets/mediaGame/CartaR4.png";
    case 5:
        return ":/assets/mediaGame/CartaR5.png";
    case 6:
        return ":/assets/mediaGame/CartaR6.png";
    case 7:
        return ":/assets/mediaGame/CartaR7.png";
    case 8:
        return ":/assets/mediaGame/CartaR8.png";
    case 9:
        return ":/assets/mediaGame/CartaR9.png";
    default:
        return ":/assets/mediaGame/ReversoCarta.png";
    }
}
//Retorna los directorios de las cartas azules
std::string Numerica::getDirectoriosAzul()const{
    switch(this->valor){
        case 0:
            return ":/assets/mediaGame/CartaA0.png";
        case 1:
            return ":/assets/mediaGame/CartaA1.png";
        case 2:
            return ":/assets/mediaGame/CartaA2.png";
        case 3:
            return ":/assets/mediaGame/CartaA3.png";
        case 4:
            return ":/assets/mediaGame/CartaA4.png";
        case 5:
            return ":/assets/mediaGame/CartaA5.png";
        case 6:
            return ":/assets/mediaGame/CartaA6.png";
        case 7:
            return ":/assets/mediaGame/CartaA7.png";
        case 8:
            return ":/assets/mediaGame/CartaA8.png";
        case 9:
            return ":/assets/mediaGame/CartaA9.png";
        default:
            return ":/assets/mediaGame/ReversoCarta.png";
    }
}
//Retorna los directorios de las cartas amarillas
std::string Numerica::getDirectoriosAmarillo()const{
    switch(this->valor){
        case 0:
            return ":/assets/mediaGame/CartaY0.png";
        case 1:
            return ":/assets/mediaGame/CartaY1.png";
        case 2:
            return ":/assets/mediaGame/CartaY2.png";
        case 3:
            return ":/assets/mediaGame/CartaY3.png";
        case 4:
            return ":/assets/mediaGame/CartaY4.png";
        case 5:
            return ":/assets/mediaGame/CartaY5.png";
        case 6:
            return ":/assets/mediaGame/CartaY6.png";
        case 7:
            return ":/assets/mediaGame/CartaY7.png";
        case 8:
            return ":/assets/mediaGame/CartaY8.png";
        case 9:
            return ":/assets/mediaGame/CartaY9.png";
        default:
            return ":/assets/mediaGame/ReversoCarta.png";
    }
}
//Retorna los directorios de las cartas verdes
std::string Numerica::getDirectoriosVerde()const{
    switch(this->valor){
    case 0:
        return ":/assets/mediaGame/CartaV0.png";
    case 1:
        return ":/assets/mediaGame/CartaV1.png";
    case 2:
        return ":/assets/mediaGame/CartaV2.png";
    case 3:
        return ":/assets/mediaGame/CartaV3.png";
    case 4:
        return ":/assets/mediaGame/CartaV4.png";
    case 5:
        return ":/assets/mediaGame/CartaV5.png";
    case 6:
        return ":/assets/mediaGame/CartaV6.png";
    case 7:
        return ":/assets/mediaGame/CartaV7.png";
    case 8:
        return ":/assets/mediaGame/CartaV8.png";
    case 9:
        return ":/assets/mediaGame/CartaV9.png";
    default:
        return ":/assets/mediaGame/ReversoCarta.png";
    }
}


//=========FIN DEL APARTADO DE METODOS QUE PERMITEN RETORNAR EL COLOR EN BASE AL NUMERO========

Numerica::~Numerica(){

}
