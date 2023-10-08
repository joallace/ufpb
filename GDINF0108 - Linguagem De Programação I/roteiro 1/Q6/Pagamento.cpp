#include "Pagamento.h"

double Pagamento::getValorPagamento(){
    return valorPagamento;
}

std::string Pagamento::getNomeDoFuncionario(){
    return nomeDoFuncionario;
}
void Pagamento::setValorPagamento(double valor){
    valorPagamento = valor;
}

void Pagamento::setNomeDoFuncionario(std::string nome){
    nomeDoFuncionario = nome;
}
