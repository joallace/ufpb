#ifndef PAGAMENTO_H
#define PAGAMENTO_H
#include <string>


class Pagamento{
    double valorPagamento;
    std::string nomeDoFuncionario;

    public:
        double getValorPagamento();
        std::string getNomeDoFuncionario();
        void setValorPagamento(double), setNomeDoFuncionario(std::string);
};

#endif // PAGAMENTO_H
