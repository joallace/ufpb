#ifndef DESPESA_H
#define DESPESA_H
#include <string>


class Despesa{
    double valor;
    std::string tipoDeGasto;

    public:
        double getValor();
        std::string getTipoDeGasto();
        void setValor(double), setTipoDeGasto(std::string);
};

#endif // DESPESA_H
