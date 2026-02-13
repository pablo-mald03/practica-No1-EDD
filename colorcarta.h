#ifndef COLORCARTA_H
#define COLORCARTA_H

//Enums utilizados para poder verificar el color de la carta
enum class TipoColor {
    ROSA,
    VIOLETA,
    TURQUESA,
    NARANJA,
    AZUL,
    ROJO,
    AMARILLO,
    VERDE,
};


class ColorCarta
{

private:
    TipoColor color;

public:
    ColorCarta(const TipoColor &_color);
    ~ColorCarta();

    //Metodos getter y setter
    void setColor(const TipoColor &_color);
    TipoColor getColorCarta();

    //sobrecarga de operador igual
    bool operator==(const ColorCarta& otro) const;

};

#endif // COLORCARTA_H
