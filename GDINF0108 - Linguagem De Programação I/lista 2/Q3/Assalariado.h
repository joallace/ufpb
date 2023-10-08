#ifndef ASSALARIADO_H
#define ASSALARIADO_H

#include "Funcionario.cpp"


class Assalariado : public Funcionario{
    double salario;
    public:
        double calculaSalario();
        Assalariado(std::string, std::string, double);

};

#endif // ASSALARIADO_H
