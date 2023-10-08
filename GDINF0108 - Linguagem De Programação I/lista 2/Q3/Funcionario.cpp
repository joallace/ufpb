#ifndef FUNCIONARIO_CPP
#define FUNCIONARIO_CPP

#include "Funcionario.h"

std::string Funcionario::getNome(){
    return nome;
}

std::string Funcionario::getMatricula(){
    return matricula;
}

void Funcionario::setNome(std::string nome){
    this->nome = nome;
}

void Funcionario::setMatricula(std::string matricula){
    this->matricula = matricula;
}

Funcionario::Funcionario(std::string nome, std::string matricula){
    this->nome = nome;
    this->matricula = matricula;
    atividade = 1;
}

#endif // FUNCIONARIO_CPP
