#ifndef CIRCULO_H
#define CIRCULO_H
#include "FiguraGeometrica.h"

class Circulo : FiguraGeometrica{
    public:
        Circulo();
        std::string getNome();
        double calcularArea(double raio);
};


#endif // CIRCULO_H
