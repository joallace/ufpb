#include <iostream>
#include "ContaEspecial.h"

int main(){
    Conta c1 = Conta("Marineldson", 874.3, 1264.87, 555454);
    ContaEspecial ce1= ContaEspecial("Topervaldo", 9879.91, 85321.40, 1);

    c1.definirLimite();
    ce1.definirLimite();

    std::cout<<"-----------Antes-----------\n";

    std::cout<<"Nome :" + c1.getNome() + "\n";
    std::cout<<"Salario :" << c1.getSalario() << "\n";
    std::cout<<"Saldo :" << c1.getSaldo() << "\n";
    std::cout<<"Limite :" << c1.getLimite() << "\n";
    std::cout<<"Conta :" << c1.getConta() << "\n\n";

    std::cout<<"Nome :" + ce1.getNome() + "\n";
    std::cout<<"Salario :" << ce1.getSalario() << "\n";
    std::cout<<"Saldo :" << ce1.getSaldo() << "\n";
    std::cout<<"Limite :" << ce1.getLimite() << "\n";
    std::cout<<"Conta :" << ce1.getConta() << "\n\n\n";

    c1.sacar(34.90);
    c1.depositar(c1.getSalario());

    ce1.sacar(2503.60);
    ce1.depositar(ce1.getSalario());

    std::cout<<"-----------Depois-----------\n";

    std::cout<<"Nome :" + c1.getNome() + "\n";
    std::cout<<"Salario :" << c1.getSalario() << "\n";
    std::cout<<"Saldo :" << c1.getSaldo() << "\n";
    std::cout<<"Limite :" << c1.getLimite() << "\n";
    std::cout<<"Conta :" << c1.getConta() << "\n\n";

    std::cout<<"Nome :" + ce1.getNome() + "\n";
    std::cout<<"Salario :" << ce1.getSalario() << "\n";
    std::cout<<"Saldo :" << ce1.getSaldo() << "\n";
    std::cout<<"Limite :" << ce1.getLimite() << "\n";
    std::cout<<"Conta :" << ce1.getConta() << "\n";

    return 0;
}
