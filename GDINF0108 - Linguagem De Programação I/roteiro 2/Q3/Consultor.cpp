#include "Consultor.h"

double Consultor::getSalario(){
    return salario + salario/10;
}

double Consultor::getSalario(float percentual){
    return salario + salario*percentual;
}

Consultor::Consultor(std::string nome, std::string matricula, double salario):Funcionario(nome,  matricula, salario){}
