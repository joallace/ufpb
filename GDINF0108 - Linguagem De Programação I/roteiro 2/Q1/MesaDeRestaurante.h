#ifndef MESADERESTAURANTE_H
#define MESADERESTAURANTE_H

#define QNT_PEDIDOS 10
#include "Pedido.cpp"

class MesaDeRestaurante{
    Pedido pedidos[QNT_PEDIDOS] = {};

    public:
        void adicionaPedido(Pedido pedido);
        void zeraPedidos();
        double calculaTotal();
};
#endif // MESADERESTAURANTE_H
