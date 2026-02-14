#ifndef NUMERICA_H
#define NUMERICA_H

#include "modelo.h"

class Numerica:public Modelo
{

private:
    int valor;

    std::string getDirectoriosRosa() const;
    std::string getDirectoriosVioleta() const;
    std::string getDirectoriosTurquesa() const;
    std::string getDirectoriosNaranja() const;
    std::string getDirectoriosRojo() const;
    std::string getDirectoriosAzul() const;
    std::string getDirectoriosAmarillo() const;
    std::string getDirectoriosVerde() const;



public:
    Numerica(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado, int _valor);

    int getValor() const;
    void setValor(int _valor);

    ~Numerica();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;

};

#endif // NUMERICA_H
