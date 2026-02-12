#ifndef COLORCARTA_H
#define COLORCARTA_H

#include<string>

class ColorCarta
{

private:
    std::string color;

public:
    ColorCarta(const std::string &_color);
    ~ColorCarta();

    //Metodos getter y setter
    void setColor(const std::string &_color);
    std::string getColor();

    //sobrecarga de operador igual
    bool operator==(const ColorCarta& otro) const;

};

#endif // COLORCARTA_H
