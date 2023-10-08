#ifndef POUPANCA_H
#define POUPANCA_H

#include <Conta.h>

class Poupanca : public Conta
{
    int variacao;
    double taxaRendimento;

    public:
        Poupanca(std::string nomeCliente, int numero, double saldo, int variacao, double taxaRendimento);

        int getVariacao() { return variacao; }
        void setVariacao(int val) { variacao = val; }
        double getTaxaRendimento() { return taxaRendimento; }
        void setTaxaRendimento(double val) { taxaRendimento = val; }

        double render();
};

#endif // POUPANCA_H
