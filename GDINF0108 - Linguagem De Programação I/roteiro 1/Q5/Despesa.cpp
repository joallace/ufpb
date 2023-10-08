#include "Despesa.h"

double Despesa::getValor(){
    return valor;
}

std::string Despesa::getTipoDeGasto(){
    return tipoDeGasto;
}
void Despesa::setValor(double valor){
    this->valor = valor;
}

void Despesa::setTipoDeGasto(std::string tipo){
    tipoDeGasto = tipo;
}
