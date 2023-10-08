#include <iostream>
#include <ContaEspecial.h>
#include <Poupanca.h>

int main(){
    ContaCorrente cc = ContaCorrente("Jubiley Santos", 302930, 3219.80, 1256.30);
    ContaEspecial ce = ContaEspecial("Infelizardo Tristonildo", 767998, 3.50, 10);
    Poupanca p = Poupanca("Burguenildo Ricardo", 99999, 9999.99, 1, 3.40);

    std::cout << "\tANTES:\n";
    std::cout << "Conta Corrente\n";
    std::cout << "Nome: " << cc.getNomeCliente() << "\n";
    std::cout << "Numero da conta: " << cc.getNumero() << "\n";
    std::cout << "Saldo: " << cc.getSaldo() << "\n";
    std::cout << "Salario: " << cc.getSalario() << "\n";
    std::cout << "Limite: " << cc.getLimite() << "\n\n";

    std::cout << "Conta Especial\n";
    std::cout << "Nome: " << ce.getNomeCliente() << "\n";
    std::cout << "Numero da conta: " << ce.getNumero() << "\n";
    std::cout << "Saldo: " << ce.getSaldo() << "\n";
    std::cout << "Salario: " << ce.getSalario() << "\n";
    std::cout << "Limite: " << ce.getLimite() << "\n\n";

    std::cout << "Conta Poupanca\n";
    std::cout << "Nome: " << p.getNomeCliente() << "\n";
    std::cout << "Numero da conta: " << p.getNumero() << "\n";
    std::cout << "Saldo: " << p.getSaldo() << "\n";
    std::cout << "Variacao: " << p.getVariacao() << "\n";
    std::cout << "Taxa de rendimento: " << p.getTaxaRendimento() << "\n\n\n";

    cc.sacar(4000);
    ce.depositar(34.50);
    p.render();

    std::cout << "\tDEPOIS:\n";
        std::cout << "Conta Corrente\n";
    std::cout << "Nome: " << cc.getNomeCliente() << "\n";
    std::cout << "Numero da conta: " << cc.getNumero() << "\n";
    std::cout << "Saldo: " << cc.getSaldo() << "\n";
    std::cout << "Salario: " << cc.getSalario() << "\n";
    std::cout << "Limite: " << cc.getLimite() << "\n\n";

    std::cout << "Conta Especial\n";
    std::cout << "Nome: " << ce.getNomeCliente() << "\n";
    std::cout << "Numero da conta: " << ce.getNumero() << "\n";
    std::cout << "Saldo: " << ce.getSaldo() << "\n";
    std::cout << "Salario: " << ce.getSalario() << "\n";
    std::cout << "Limite: " << ce.getLimite() << "\n\n";

    std::cout << "Conta Poupanca\n";
    std::cout << "Nome: " << p.getNomeCliente() << "\n";
    std::cout << "Numero da conta: " << p.getNumero() << "\n";
    std::cout << "Saldo: " << p.getSaldo() << "\n";
    std::cout << "Variacao: " << p.getVariacao() << "\n";
    std::cout << "Taxa de rendimento: " << p.getTaxaRendimento() << "\n\n\n";

    return 0;
}
