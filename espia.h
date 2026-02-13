#ifndef ESPIA_H
#define ESPIA_H

#include"modelo.h"

class Espia:public Modelo
{
public:
    Espia(const ColorCarta&_colorRef, const std::string &_nombre,const std::string &_lado);
    ~Espia(); 
    //Metodo de revelacion
    void revelarMazo();

    //Metodo sobreescrito de imagen
    std::string getPathImagen() const override;
};

#endif // ESPIA_H
