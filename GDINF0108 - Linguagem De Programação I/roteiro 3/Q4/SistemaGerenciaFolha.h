#ifndef SISTEMAGERENCIAFOLHA_H
#define SISTEMAGERENCIAFOLHA_H

#include "Funcionario.cpp"
#include "FuncionarioNaoExisteException.h"
#include "OrcamentoEstouradoException.h

#define QNTD_FUNCIONARIOS 10

class SistemaGerenciaFolha
{
    Funcionario *funcionarios[QNTD_FUNCIONARIOS] = {};

    public:
        //SistemaGerenciaFolha();
        void setFuncionarios(Funcionario*);
        double calculaValorTotalFolha();
        double consultaSalarioFuncionario(std::string matricula);

};

#endif // SISTEMAGERENCIAFOLHA_H
