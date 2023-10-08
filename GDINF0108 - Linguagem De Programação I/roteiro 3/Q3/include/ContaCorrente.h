#ifndef CONTACORRENTE_H
#define CONTACORRENTE_H

#include <Conta.h>


class ContaCorrente : public Conta
{
    double salario;
    double limite;

    public:
        ContaCorrente(std::string nomeCliente, int numero, double saldo, double salario);

        double getSalario() { return salario; }
        void setSalario(double val) { salario = val; }

        double getLimite() { return limite; }
        void setLimite(double val) { limite = val; }

        virtual double definirLimite();
};

#endif // CONTACORRENTE_H
