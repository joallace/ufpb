#include "Quadrado.h"

Quadrado::Quadrado(){
    nome = "Quadrado";
}

std::string Quadrado::getNome(){
    return nome;
}

double Quadrado::calcularArea(double lado){
    return lado*lado;
}
