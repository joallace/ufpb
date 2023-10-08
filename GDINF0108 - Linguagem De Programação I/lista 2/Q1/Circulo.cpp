#include "Circulo.h"
# define M_PI          3.141592653589793238462643383279502884L /* pi */

Circulo::Circulo(){
    nome = "Circulo";
}

std::string Circulo::getNome(){
    return nome;
}

double Circulo::calcularArea(double raio){
    return M_PI*raio*raio;
}
