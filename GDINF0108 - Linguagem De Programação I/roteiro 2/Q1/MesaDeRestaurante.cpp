#include "MesaDeRestaurante.h"

void MesaDeRestaurante::adicionaPedido(Pedido pedido){
    int flag = 0, flagVazio;

    for(int i = QNT_PEDIDOS; i > 0; i--){
        if(pedido.num == pedidos[i].num)
            flag = i;
        if(pedidos[i].quantidade == 0)
            flagVazio = i;
    }

    if(flag)
        pedidos[flag].quantidade++;
    else
        pedidos[flagVazio] = pedido;
}

void MesaDeRestaurante::zeraPedidos(){
    for(int i = 0; i < QNT_PEDIDOS; i++)
        pedidos[i].quantidade = 0;
}

double MesaDeRestaurante::calculaTotal(){
    double soma = 0;
    for(int i = 0; i < QNT_PEDIDOS; i++)
        soma += pedidos[i].preco * pedidos[i].quantidade;

    return soma;
}
