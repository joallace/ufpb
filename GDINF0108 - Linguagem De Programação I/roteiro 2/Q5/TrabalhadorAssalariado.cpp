#include "TrabalhadorAssalariado.h"

TrabalhadorAssalariado::TrabalhadorAssalariado(std::string nome, double salario):Trabalhador(nome, salario){}

double TrabalhadorAssalariado::calcularPagamentoSemanal(){
    return salario/4;
}
