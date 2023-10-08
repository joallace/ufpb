#ifndef TRABALHADOR_A_H
#define TRABALHADOR_A_H
#include "Trabalhador.cpp"

class TrabalhadorAssalariado : public Trabalhador{
    public:
        TrabalhadorAssalariado(std::string nome, double salario);
        double calcularPagamentoSemanal();
};

#endif // TRABALHADOR_A_H
