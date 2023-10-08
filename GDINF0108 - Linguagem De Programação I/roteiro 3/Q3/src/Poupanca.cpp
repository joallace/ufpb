#include "Poupanca.h"

Poupanca::Poupanca(std::string nomeCliente, int numero, double saldo, int variacao, double taxaRendimento) : Conta(nomeCliente, numero, saldo)
{
    setVariacao(variacao);
    if(variacao == 1)
        taxaRendimento += 0.5;
    setTaxaRendimento(taxaRendimento);
}

double Poupanca::render(){
    setSaldo(getSaldo()*1+taxaRendimento);
    return getSaldo();
}
