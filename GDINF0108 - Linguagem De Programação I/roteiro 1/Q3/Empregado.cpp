#include "Empregado.h"

void Empregado::setNome(std::string nome){
    this->nome = nome;
}

void Empregado::setSobrenome(std::string nome){
    this->sobrenome = sobrenome;
}

void Empregado::setSalario(double salario){
    this->salario = salario;
}

std::string Empregado::getNome(){
    return nome;
}

std::string Empregado::getSobrenome(){
    return sobrenome;
}

double Empregado::getSalario(){
    return salario;
}

Empregado::Empregado(std::string nome, std::string sobrenome, double salario){
    setNome(nome);
    setSobrenome(sobrenome);
    setSalario(salario);
}
