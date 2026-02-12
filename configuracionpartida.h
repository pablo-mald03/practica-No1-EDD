#ifndef CONFIGURACIONPARTIDA_H
#define CONFIGURACIONPARTIDA_H


struct DatosConfiguracion;


class ConfiguracionPartida
{

private:
    bool stacking;
    bool retoMas4;
    bool modoRobo;
    bool gritoUno;
    bool ganarNegra;
    bool flip;

public:

    ConfiguracionPartida(DatosConfiguracion* &config);
    ~ConfiguracionPartida();

    //Metodos getters para saber la partida
    bool esStacking()const;
    bool esRetoMas4()const;
    bool esModoRobo()const;
    bool esGritoUno()const;
    bool esGanarNegra()const;
    bool esFlip()const;
};

#endif // CONFIGURACIONPARTIDA_H
