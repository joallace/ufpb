#ifndef CONTAESPECIAL_H
#define CONTAESPECIAL_H

#include <Conta.h>


class ContaEspecial : public Conta
{
    public:
        void definirLimite();
        ContaEspecial(std::string nome, double salario, double saldo, int conta);
};

#endif // CONTAESPECIAL_H
