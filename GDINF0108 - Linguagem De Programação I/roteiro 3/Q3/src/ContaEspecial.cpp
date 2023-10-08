#include "ContaEspecial.h"
#include <iostream>

ContaEspecial::ContaEspecial(std::string nomeCliente, int numero, double saldo, double salario) :
ContaCorrente(nomeCliente, numero, saldo, salario){
    definirLimite();
}

double ContaEspecial::definirLimite()
{
    setLimite(4*getSalario());
    return getLimite();
}
