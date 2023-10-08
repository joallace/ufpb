#ifndef TRABALHADOR_H_H
#define TRABALHADOR_H_H
#include "Trabalhador.cpp"

class TrabalhadorPorHora : public Trabalhador{
    double valorDaHora;
    public:
        TrabalhadorPorHora(std::string nome, double valorDaHora);
        double calcularPagamentoSemanal(int horas);
};

#endif // TRABALHADOR_H_H
