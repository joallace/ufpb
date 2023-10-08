#include "Horista.h"

Horista::Horista(std::string nome, std::string matricula, double salario):Funcionario(nome, matricula){
    salarioPorHora = salario;
}

void Horista::setHoras(double horas){
    horasTrabalhadas = horas;
}

double Horista::calculaSalario(){
    if (horasTrabalhadas > 40)
        return ((horasTrabalhadas-40)*1.5*salarioPorHora) + 40*salarioPorHora;
    else
        return horasTrabalhadas*salarioPorHora;
}
