#include "Medico.h"

Medico::Medico(std::string nome, std::string altura, std::string peso){
    setNome(nome);
    setAltura(altura);
    setPeso(peso);
}

std::string Medico::getNome(){
    return nome;
}

void Medico::setNome(std::string val){
    nome = val;
}

std::string Medico::getAltura(){
    return altura;
}

void Medico::setAltura(std::string val){
    altura = val;
}

std::string Medico::getPeso(){
    return peso;
}

std::string Medico::getEspecialidade(){
    return nomeEspecialidade;
}

void Medico::setEspecialidade(std::string val){
    nomeEspecialidade = val;
}


void Medico::setPeso(std::string val){
    peso = val;
}
