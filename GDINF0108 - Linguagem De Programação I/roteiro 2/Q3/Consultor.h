#ifndef CONSULTOR_DEF
#define CONSULTOR_DEF
#include "Funcionario.h"

class Consultor : public Funcionario{
    public:
        double getSalario();
        double getSalario(float percentual);
        Consultor(std::string nome, std::string matricula, double salario);

};

#endif // CONSULTOR_DEF
