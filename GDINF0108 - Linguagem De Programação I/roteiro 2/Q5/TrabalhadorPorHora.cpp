#include "TrabalhadorPorHora.h"

TrabalhadorPorHora::TrabalhadorPorHora(std::string nome, double valorDaHora):Trabalhador(nome, 0){
    this->valorDaHora = valorDaHora;
}

double TrabalhadorPorHora::calcularPagamentoSemanal(int horas){
    if(horas <= 40)
        salario = valorDaHora * horas;
    else
        salario = valorDaHora * 40 + valorDaHora * (horas - 40)*1.5;

    return salario;
}
