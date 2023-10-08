#include <iostream>
#include "Pessoa.cpp"

int main(){
    int idade;
    std::string numero;

    Pessoa ome = Pessoa("Carlos Louis");
    Pessoa muie = Pessoa("Carlotte Luiza", 54, "(11)99999-9999");


    std::cout << "Agora que seu nome eh " << ome.getNome() << ". Digite sua idade, e telefone"<<std::endl;
    std::cin >> idade;
    std::cin >> numero;
    std::cout << std::endl;

    ome.setIdade(idade);
    ome.setTelefone(numero);

    std::cout << "Sua muie eh " << muie.getNome() << "." << std::endl;
    std::cout << "Suas idades somam: " << muie.getIdade() + ome.getIdade() << "." << std::endl;
    std::cout << "Numero dela: " << muie.getTelefone() << " ;)" << std::endl;

    return 0;
}
