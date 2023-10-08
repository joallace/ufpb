#include <iostream>
#include "Invoice.cpp"

using namespace std;

int main(){
    int qntd, num;
    string descricao;
    double preco;

    cout<<"Insira o numero do produto: ";
    cin>>num;

    cout<<"Insira a quantidade comprada do produto: ";
    cin>>qntd;

    cout<<"Insira a descricao do produto: ";
    cin>>descricao;

    cout<<"Insira o preco do produto: ";
    cin>>preco;

    Invoice fatura = Invoice(num, qntd, descricao, preco);

    cout<<"O total eh: R$"<<fatura.getInvoiceAmount()<<endl;;
}
