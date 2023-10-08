#ifndef QUADRADO_H
#define QUADRADO_H
#include "FiguraGeometrica.h"

class Quadrado : FiguraGeometrica{
    public:
        Quadrado();
        std::string getNome();
        double calcularArea(double lado);
};


#endif // QUADRADO_H
