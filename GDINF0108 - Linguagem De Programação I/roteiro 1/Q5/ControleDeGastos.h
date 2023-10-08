#ifndef CDG_H
#define CDG_H
#include "Despesa.cpp"
#define QNT_D 10

class ControleDeGastos{
    Despesa despesas[QNT_D] = {};

    public:
        void setDespesa(Despesa, int);
        double calculaTotalDeDespesas();
        bool existeDespesaDoTipo(std::string);
};

#endif
