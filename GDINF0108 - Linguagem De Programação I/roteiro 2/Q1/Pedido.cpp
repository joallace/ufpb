#include "Pedido.h"


Pedido::Pedido(): num(0), quantidade(0),
preco(0), descricao(""){}

Pedido::Pedido(int n, int qntd, double price, std::string descri):
num(n), quantidade(qntd), preco(price), descricao(descri){}


/*
Pedido::Pedido(){
    num = 0;
    quantidade = 0;
    preco = 0;
    descricao = "";
}
*/


