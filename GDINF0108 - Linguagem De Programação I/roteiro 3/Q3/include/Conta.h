#ifndef CONTA_H
#define CONTA_H

#include <string>

class Conta
{
    std::string nomeCliente;
    int numero;
    double saldo;

    public:
        Conta(std::string nomeCliente, int numero, double saldo);

        std::string getNomeCliente() { return nomeCliente; }
        void setNomeCliente(std::string val) { nomeCliente = val; }

        int getNumero() { return numero; }
        void setNumero(int val) { numero = val; }

        double getSaldo() { return saldo; }
        void setSaldo(double val) { saldo = val; }

        void sacar(double valor);
        void depositar(double valor);

};

#endif // CONTA_H
