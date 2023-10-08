#include "Endereco.h"

Endereco::Endereco(std::string rua, std::string bairro, std::string cidade,
                   std::string estado, std::string numero, std::string cep){
    this->rua = rua;
    this->bairro = bairro;
    this->cidade = cidade;
    this->estado = estado;
    this->numero = numero;
    this->cep = cep;
}

Endereco::Endereco(){
    this->rua = "";
    this->bairro = "";
    this->cidade = "";
    this->estado = "";
    this->numero = "";
    this->cep = "";
}

std::string Endereco::toString(){
    return "Rua: " + rua + "\n"+
           "Bairro: " + bairro + "\n"+
           "Cidade: " + cidade + "\n"+
           "Estado: " + estado + "\n"+
           "Numero: " + numero + "\n"+
           "CEP: " + cep + "\n";
}

