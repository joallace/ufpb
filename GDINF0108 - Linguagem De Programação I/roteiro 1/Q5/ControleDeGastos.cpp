#include "ControleDeGastos.h"

void ControleDeGastos::setDespesa(Despesa d, int pos){
    despesas[pos] = d;
}

double ControleDeGastos::calculaTotalDeDespesas(){
    double soma = 0;

    for(int i = 0; i < QNT_D; i++){
        soma += despesas[i].getValor();
    }

    return soma;
}

bool ControleDeGastos::existeDespesaDoTipo(std::string tipo){
    bool flag = false;

    for(int i = 0; i < QNT_D; i++){
        if(tipo == despesas[i].getTipoDeGasto())
            flag = true;
    }

    return flag;
}
