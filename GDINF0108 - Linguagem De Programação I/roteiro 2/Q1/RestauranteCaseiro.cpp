#include "RestauranteCaseiro.h"

void RestauranteCaseiro::adicionaPedido(Pedido pedido, int mesa){
    mesas[mesa].adicionaPedido(pedido);
}

double RestauranteCaseiro::calculaTotalRestaurante(){
    double soma = 0;

    for(int i = 0; i < QNT_MESAS; i++)
        soma += mesas[i].calculaTotal();

    return soma;
}
