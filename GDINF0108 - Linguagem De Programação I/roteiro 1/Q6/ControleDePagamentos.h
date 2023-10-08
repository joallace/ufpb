#ifndef CDP_H
#define CDP_H
#include "Pagamento.cpp"
#define QNT_P 10

class ControleDePagamentos{
    Pagamento pagamentos[QNT_P] = {};

    public:
        void setPagamento(Pagamento, int);
        double calculaTotalDePagamentos();
        bool existePagamentoParaFuncionario (std::string);
};

#endif
