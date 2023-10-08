#include <iostream>
#include "Pessoa.cpp"

int main(){
    Endereco e1 = Endereco("Rua do CI", "Bairro do CI", "Cidade do CI", "Estado do CI",
                           "629", "58000-000");
    Pessoa p1 = Pessoa("Clodoaldo", "(83)98888-8888", e1);

    std::cout << "Nome: " + p1.getNome()<<std::endl;
    std::cout << "Telefone antes: " << p1.getTelefone()<<std::endl;
    p1.setTelefone("(81)98887-8888");
    std::cout << "Telefone depois: " << p1.getTelefone()<<std::endl;
    std::cout << p1.toString();
}
