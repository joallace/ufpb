#include "Apartamento.h"

Apartamento::Apartamento():Imovel(){
    setPosicao("");
    setNumQuartos(0);
    setValorCond(0);
    setVagasGaragem(0);
    tipo = APARTAMENTO;
}

Apartamento::Apartamento(Endereco endereco, tNegocio negocio, double valor, double area,
                         double valC, int nQrts, int vagas, std::string posicao) :
                         Imovel(endereco, negocio, valor, area)
{
    setPosicao(posicao);
    setNumQuartos(nQrts);
    setValorCond(valC);
    setVagasGaragem(vagas);
    tipo = APARTAMENTO;
}

std::string Apartamento::getDescricao(){
    return "Tipo de Imovel: Apartamento\n" +
           Imovel::getDescricao() + "\n" +

           "\n->Caracteristicas do Apartamento\n" +
           "\t->Quantidade de quartos: " + std::to_string(numQuartos) + "\n" +
           "\t->Quantidade de vagas na garagem: " + std::to_string(vagasGaragem) + "\n" +
           "\t->Valor do condominio: R$" + std::to_string(valorCondominio) + "\n" +
           "\t->Posicao: " + posicao + "\n" +
           "\t->Area total: " + std::to_string(getArea()) + "\n";
}

std::string Apartamento::getDescricaoPure(){
    return "APARTAMENTO\n" +
           Imovel::getDescricaoPure() +
           std::to_string(numQuartos) + "\n" +
           std::to_string(vagasGaragem) + "\n" +
           std::to_string(valorCondominio) + "\n" +
           posicao + "\n" +
           std::to_string(getArea()) + "\n\n";
}

std::string Apartamento::getPosicao()
{
    return posicao;
}

void Apartamento::setPosicao(std::string posicao)
{
    this->posicao = posicao;
}

int Apartamento::getNumQuartos()
{
    return numQuartos;
}

void Apartamento::setNumQuartos(int nQrts)
{
    this->numQuartos = nQrts;
}

double Apartamento::getValorCond()
{
    return valorCondominio;
}

void Apartamento::setValorCond(double valC)
{
    valorCondominio = valC;
}

int Apartamento::getVagasGaragem()
{
    return vagasGaragem;
}

void Apartamento::setVagasGaragem(int vagas)
{
    vagasGaragem = vagas;
}
