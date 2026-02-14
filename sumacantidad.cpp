#include "sumacantidad.h"

SumaCantidad::SumaCantidad(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor)
    :Modelo(_colorRef,_nombre,_lado,TipoCarta::SumarCantidad),valorSuma(_valor)
{

}

//Metodos getters y setters
int SumaCantidad::getValorSuma(){
    return this->valorSuma;
}

void SumaCantidad::setValorSuma(int _valor){
    this->valorSuma = _valor;
}

void SumaCantidad::sumarCantidad(){

}

//Metodo que retorna el valor de imagen de la carta
std::string SumaCantidad::getPathImagen() const{

    if(Modelo::getLado() == "claro"){
        if(Modelo::getColor().getColorCarta() == TipoColor::AMARILLO){

            if(this->valorSuma == 1){
                return ":/assets/mediaGame/CartaYMas1.png";
            }
            else if(this->valorSuma == 2){
                return ":/assets/mediaGame/CartaYMas2.png";
            }
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROJO){
            if(this->valorSuma == 1){
                return ":/assets/mediaGame/CartaRMas1.png";
            }
            else if(this->valorSuma == 2){
                return ":/assets/mediaGame/CartaRMas2.png";
            }
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::AZUL){

            if(this->valorSuma == 1){
                return ":/assets/mediaGame/CartaAMas1.png";
            }
            else if(this->valorSuma == 2){
                return ":/assets/mediaGame/CartaAMas2.png";
            }
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::VERDE){
            if(this->valorSuma == 1){
                return ":/assets/mediaGame/CartaVMas1.png";
            }
            else if(this->valorSuma == 2){
                return ":/assets/mediaGame/CartaVMas2.png";
            }
        }

    }else if(Modelo::getLado() == "oscuro"){

        if(Modelo::getColor().getColorCarta() == TipoColor::VIOLETA && this->valorSuma == 3){
            return ":/assets/mediaGame/CartaVIMas3.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::TURQUESA && this->valorSuma == 3){
            return ":/assets/mediaGame/CartaTMas3.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::ROSA && this->valorSuma == 3){
            return ":/assets/mediaGame/CartaROMas3.png";
        }
        else if(Modelo::getColor().getColorCarta() == TipoColor::NARANJA && this->valorSuma == 3){
            return ":/assets/mediaGame/CartaNMas3.png";
        }
    }
    return ":/assets/mediaGame/ReversoCarta.png";
}



SumaCantidad::~SumaCantidad(){

}
