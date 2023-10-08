#include "Invoice.h"

double Invoice::getInvoiceAmount(){
    int total;

    total = qntd*preco;
    if(total > 0)
        return total;
    else
        return 0;
}

int Invoice::getNum(){
    return num;
}

int Invoice::getQntd(){
    return qntd;
}

std::string Invoice::getDescricao(){
    return descricao;
}

double Invoice::getPreco(){
    return preco;
}

void Invoice::setNum(int num){
    this->num = num;
}

void Invoice::setQntd(int qntd){
    if(qntd >= 0)
        this->qntd = qntd;
    else
        this->qntd = 1;
}

void Invoice::setDescricao(std::string descricao){
    this->descricao = descricao;
}

void Invoice::setPreco(double preco){
    if(preco > 0)
        this->preco = preco;
    else
        this->preco = 1;
}

Invoice::Invoice(int num, int qntd, std::string descricao, double preco){
    setNum(num);

    setQntd(qntd);

    setDescricao(descricao);

    setPreco(preco);
}
