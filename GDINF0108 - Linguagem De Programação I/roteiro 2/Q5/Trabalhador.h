#ifndef TRABALHADOR_H
#define TRABALHADOR_H
#include <string>

class Trabalhador{
    std::string nome;

    public:
        double salario;
        Trabalhador(std::string nome, double salario);
        double calcularPagamentoSemanal(int horas);
};

#endif // TRABALHADOR_H
