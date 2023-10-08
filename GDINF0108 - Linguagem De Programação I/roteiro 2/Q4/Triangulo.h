#ifndef TRIANGULO_H
#define TRIANGULO_H
#include "FiguraGeometrica.h"

class Triangulo : FiguraGeometrica{
    public:
        Triangulo();
        std::string getNome();
        double calcularArea(double base, double altura);
};

#endif // TRIANGULO_H
