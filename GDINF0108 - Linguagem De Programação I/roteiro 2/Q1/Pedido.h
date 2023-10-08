#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>

class Pedido{
    public:
        int num,
            quantidade;
        double preco;
        std::string descricao;

        Pedido();
        Pedido(int, int, double, std::string);
};

#endif // PEDIDO_H
