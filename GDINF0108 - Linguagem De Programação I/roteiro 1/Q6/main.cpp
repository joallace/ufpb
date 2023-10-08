#include <iostream>
#include "ControleDePagamentos.cpp"

int main(){
    Pagamento pagm1, pagm2, pagm3;
    ControleDePagamentos controle;

    pagm1.setNomeDoFuncionario("Diana Marcia");
    pagm1.setValorPagamento(1102.75);
    controle.setPagamento(pagm1, 0);

    pagm2.setNomeDoFuncionario("Lucas Macedo");
    pagm2.setValorPagamento(1445.99);
    controle.setPagamento(pagm2, 1);

    pagm3.setNomeDoFuncionario("Dovahkin");
    pagm3.setValorPagamento(888.33);
    controle.setPagamento(pagm3, 2);

    std::cout << "Existe pagamento para \"" << pagm1.getNomeDoFuncionario() << "\"?" << std::endl;

    if(controle.existePagamentoParaFuncionario(pagm1.getNomeDoFuncionario()))
        std::cout << "Sim" << std::endl;
    else
        std::cout << "Nao" << std::endl;

    std::cout << std::endl;

    std::cout << "Total de pagamentos: R$" << controle.calculaTotalDePagamentos() << std::endl;

    return 0;
}
