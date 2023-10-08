#include "ContaCorrente.h"

ContaCorrente::ContaCorrente(std::string nomeCliente, int numero, double saldo, double salario) : Conta(nomeCliente, numero, saldo)
{
    setSalario(salario);
    definirLimite();
}


double ContaCorrente::definirLimite()
{
    return limite = 2*salario;
}
