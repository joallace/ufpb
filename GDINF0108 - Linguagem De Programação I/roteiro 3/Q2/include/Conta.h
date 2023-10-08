#ifndef CONTA_H
#define CONTA_H

#include <IConta.h>

#include <string>


class Conta : public IConta{
    protected:
        std::string nomeCliente;
        double salarioMensal, saldo, limite;
        int numeroConta;

    public:
        Conta(std::string nome, double salario, double saldo, int conta);

        std::string getNome();
        double getSalario(),
               getSaldo(),
               getLimite();
        int getConta();

        void setNome(std::string),
             setSalario(double),
             setSaldo(double),
             definirLimite(),
             setConta(int);

        void sacar(double valor);
        void depositar(double valor);
};

#endif // CONTA_H
