#include "Endereco.h"

Endereco::Endereco()
{
    rua = "";
    bairro = "";
    cidade = "";
    cep = "";
    numero = "";
}

Endereco::Endereco(std::string r,std::string b,std::string c,std::string cep,std::string num)
{
    rua = r;
    bairro = b;
    cidade = c;
    this->cep = cep;
    numero = num;
}
