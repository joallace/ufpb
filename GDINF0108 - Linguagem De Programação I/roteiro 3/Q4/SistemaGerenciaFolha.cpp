#include "SistemaGerenciaFolha.h"

static int i = 0;

void SistemaGerenciaFolha::setFuncionarios(Funcionario *f){
    funcionarios[i] = f;
    i++;
}

double SistemaGerenciaFolha::calculaValorTotalFolha(){
    double soma = 0;

    for(int j = 0; j < i; j++){
        soma+= funcionarios[j]->calculaSalario();
    }

    return soma;
}

double SistemaGerenciaFolha::consultaSalarioFuncionario(std::string matricula){
    for(int j = 0; j < i; j++)
        if(!matricula.compare(funcionarios[j]->getMatricula()))
            return (funcionarios[j]->calculaSalario());
    return 0;
}
