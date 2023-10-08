#include "ControleDePagamentos.h"

void ControleDePagamentos::setPagamento(Pagamento p, int pos){
    pagamentos[pos] = p;
}

double ControleDePagamentos::calculaTotalDePagamentos(){
    double soma = 0;

    for(int i = 0; i < QNT_P; i++){

        /* PRA DEBUGAR
        std::cout << "Soma "<< i << ": " << soma << std::endl;
        std::cout << "Valor "<< i << ": "  << pagamentos[i].getValorPagamento() << std::endl << std::endl;
        */

        soma += pagamentos[i].getValorPagamento();
    }

    return soma;
}

bool ControleDePagamentos::existePagamentoParaFuncionario(std::string nome){
    for(int i = 0; i < QNT_P; i++){
        if(nome == pagamentos[i].getNomeDoFuncionario())
            return true;
    }

    return false;
}
