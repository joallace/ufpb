#include "Pessoa.h"

Pessoa::Pessoa(std::string nome){
    this->nome = nome;
    telefone = "";
}

Pessoa::Pessoa(std::string nome, std::string telefone, Endereco endereco){
    this->nome = nome;
    this->telefone = telefone;
    this->endereco = endereco;
}

std::string Pessoa::getNome(){
    return nome;
}

void Pessoa::setTelefone(std::string telefone){
    this->telefone = telefone;
}

std::string Pessoa::getTelefone(){
    return telefone;
}

void Pessoa::setEndereco(Endereco endereco){
    this->endereco = endereco;
}

Endereco Pessoa::getEndereco(){
    return endereco;
}

std::string Pessoa::toString(){
    return endereco.toString();
}
