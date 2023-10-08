#include "ContaEspecial.h"

void ContaEspecial::definirLimite(){
    limite = 3*salarioMensal;
}

ContaEspecial::ContaEspecial(std::string nome, double salario, double saldo, int conta):Conta(nome, salario, saldo, conta){}
