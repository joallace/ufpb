#include "Triangulo.h"

Triangulo::Triangulo(){
    nome = "Triangulo";
}

std::string Triangulo::getNome(){
    return nome;
}

double Triangulo::calcularArea(double base, double altura){
    return base*altura/2;
}
