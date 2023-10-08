#include "Assalariado.h"

Assalariado::Assalariado(std::string nome, std::string matricula, double salario):Funcionario(nome, matricula){
    this->salario = salario;
}

double Assalariado::calculaSalario(){
    return salario;
}
