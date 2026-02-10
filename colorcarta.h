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

};

#endif // COLORCARTA_H
