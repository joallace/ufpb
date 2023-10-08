#ifndef HORISTA_H
#define HORISTA_H

#include "Funcionario.cpp"


class Horista : public Funcionario{
    double salarioPorHora,
           horasTrabalhadas;

    public:
        Horista(std::string nome, std::string matricula, double salario);
        void setHoras(double);
        double calculaSalario();
};

#endif // HORISTA_H
