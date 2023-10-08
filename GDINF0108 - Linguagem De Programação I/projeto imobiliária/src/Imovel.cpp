#include "Imovel.h"

Imovel::Imovel(){
    setValor(0);
    setArea(0);
}

Imovel::Imovel(Endereco endereco, tNegocio negocio, double valor, double area){
    setEndereco(endereco);
    setNegocio(negocio);
    setValor(valor);
    setArea(area);
}


std::string Imovel::getEndereco(){
    return "\t->CEP: " + endereco.cep + "\n" +
           "\t->Cidade: " + endereco.cidade + "\n" +
           "\t->Bairro: " + endereco.bairro + "\n" +
           "\t->Rua: " + endereco.rua + "\n" +
           "\t->Numero: " + endereco.numero + "\n";
}

std::string Imovel::getDescricao(){
    std::string tipoStr = (negocio == VENDA? "VENDA" : "ALUGUEL");
    std::string tipoStrLwr = (negocio == VENDA? "venda" : "aluguel");

    return "Forma de negocio: " + tipoStr + "\n" +
    "Valor de " + tipoStrLwr + ": R$" + std::to_string(valor) + "\n" +

    "\nLocalizacao\n" +
    getEndereco();
}

std::string Imovel::getDescricaoPure(){
    std::string negocioStr = (negocio == VENDA? "VENDA" : "ALUGUEL");
    return negocioStr + "\n" +
           std::to_string(valor) + "\n" +
           endereco.cep + "\n" +
           endereco.cidade + "\n" +
           endereco.bairro + "\n" +
           endereco.rua + "\n" +
           endereco.numero + "\n";
}


double Imovel::getValor(){
    return valor;
}

void Imovel::setValor(double valor){
    this->valor = valor;
}


Endereco Imovel::getEnderecoPure(){
    return endereco;
}

void Imovel::setEndereco(Endereco endereco){
    this->endereco = endereco;
}


double Imovel::getArea(){
    return area;
}

void Imovel::setArea(double area){
    this->area = area;
}


tTipo Imovel::getTipo(){
    return tipo;
}

void Imovel::setTipo(tTipo tipo){
    this->tipo = tipo;
}

tNegocio Imovel::getNegocio(){
    return negocio;
}

void Imovel::setNegocio(tNegocio negocio){
    this->negocio = negocio;
}
