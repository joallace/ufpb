#include <iostream>
#include "ControleDeGastos.cpp"

int main(){
    Despesa desp1, desp2, desp3;
    ControleDeGastos controle;

    desp1.setTipoDeGasto("Comida");
    desp1.setValor(12.75);
    controle.setDespesa(desp1, 0);

    desp2.setTipoDeGasto("Cinema");
    desp2.setValor(14.99);
    controle.setDespesa(desp2, 1);

    desp3.setTipoDeGasto("Comida");
    desp3.setValor(8.33);
    controle.setDespesa(desp3, 2);

    std::cout << "Existe despesa do tipo \"" << desp1.getTipoDeGasto() << "\"?" << std::endl;

    if(controle.existeDespesaDoTipo(desp1.getTipoDeGasto()))
        std::cout << "Sim" << std::endl;
    else
        std::cout << "Nao" << std::endl;

    std::cout << std::endl;

    std::cout << "Total de gastos: R$" << controle.calculaTotalDeDespesas() << std::endl;

    return 0;
}
