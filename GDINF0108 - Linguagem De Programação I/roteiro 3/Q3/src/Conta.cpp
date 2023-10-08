#include "Conta.h"

Conta::Conta(std::string nomeCliente, int numero, double saldo)
{
    setNomeCliente(nomeCliente);
    setNumero(numero);
    setSaldo(saldo);
}

void Conta::sacar(double valor)
{
    if(saldo < valor)
        return;
    saldo -= valor;
}

void Conta::depositar(double valor)
{
    saldo += valor;
}
