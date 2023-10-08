#include <iostream>
#include "RestauranteCaseiro.cpp"

int main(){
    RestauranteCaseiro churrasDoMelo;
    Pedido churrinha = Pedido(30, 2, 25.35, "Frago a parmegianna");

    churrasDoMelo.adicionaPedido(churrinha, 0);

    int inteiros;
    double preco;
    std::string str;


    while(true){
        std::cout << "---------==========---------" << std::endl;
        std::cout << "\tNovo Pedido" << std::endl;
        std::cout << "---------==========---------" << std::endl;

        std::cout << "Insira o numero:" << std::endl;
        std::cin >> inteiros;
        churrinha.num = inteiros;

        std::cout << "Insira a quantidade:" << std::endl;
        std::cin >> inteiros;
        churrinha.quantidade = inteiros;

        std::cout << "Insira preco:" << std::endl;
        std::cin >> preco;
        churrinha.preco = preco;

        std::cout << "Insira a descricao:" << std::endl;
        std::cin >> str;
        churrinha.descricao = str;

        std::cout << "Insira a mesa:" << std::endl;
        std::cin >> inteiros;
        churrasDoMelo.adicionaPedido(churrinha, inteiros);

        std::cout << "Deseja registrar novo pedido?" << std::endl;
        std::cin >> str;

        if(str == "nao")
            break;
    }

    std::cout << "Total arrecadado: R$" <<  churrasDoMelo.calculaTotalRestaurante();
}
