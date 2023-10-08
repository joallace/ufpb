#include "Conta.h"

std::string Conta::getNome(){
    return nomeCliente;
}

double Conta::getSalario(){
    return salarioMensal;
}

double Conta::getSaldo(){
    return saldo;
}
double Conta::getLimite(){
    return limite;
}

int Conta::getConta(){
    return numeroConta;
}

void Conta::setNome(std::string nome){
    nomeCliente = nome;
}

void Conta::setSalario(double salario){
    salarioMensal = salario;
}

void Conta::setSaldo(double saldo){
    this->saldo = saldo;
}

void Conta::definirLimite(){
    limite = 2*salarioMensal;
}

void Conta::setConta(int conta){
    numeroConta = conta;
}

void Conta::sacar(double valor){
    if(valor > saldo)
        throw SaldoNaoDisponivelException();
    saldo = saldo - valor;
}

void Conta::depositar(double valor){
    //DEBUG:std::cout << "\n\nDepositar :" << valor <<  "\n\n";
    saldo = saldo + valor;
}

Conta::Conta(std::string nome, double salario, double saldo, int conta){
    setNome(nome);
    setSalario(salario);
    setSaldo(saldo);
    setConta(conta);
}
