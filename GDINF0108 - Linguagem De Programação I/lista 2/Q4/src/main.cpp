#include <iostream>

#include <Cirurgiao.h>
#include <Otorrino.h>
#include <Ginecologista.h>
#include <Oftalmologista.h>

int main(){
    Cirurgiao c1 = Cirurgiao("Jubiley Fernando", "1,67", "78,90");
    Otorrino ot1 = Otorrino("Jordao Abreu", "1,78", "84,73");
    Ginecologista g1 = Ginecologista("Jonas Matias", "1,20", "52,89");
    Oftalmologista of1 = Oftalmologista("Julio Augusto", "1,74", "98,45");

    std::cout << "Ficha do " << c1.getEspecialidade() << ":\n";
    std::cout << "Nome: " << c1.getNome() << "\n";
    std::cout << "Altura: " << c1.getAltura() << "m\n";
    std::cout << "Peso: " << c1.getPeso() << "kg\n\n";

    std::cout << "Ficha do " << ot1.getEspecialidade() << ":\n";
    std::cout << "Nome: " << ot1.getNome() << "\n";
    std::cout << "Altura: " << ot1.getAltura() << "m\n";
    std::cout << "Peso: " << ot1.getPeso() << "kg\n\n";

    std::cout << "Ficha do " << g1.getEspecialidade() << ":\n";
    std::cout << "Nome: " << g1.getNome() << "\n";
    std::cout << "Altura: " << g1.getAltura() << "m\n";
    std::cout << "Peso: " << g1.getPeso() << "kg\n\n";

    std::cout << "Ficha do " << of1.getEspecialidade() << ":\n";
    std::cout << "Nome: " << of1.getNome() << "\n";
    std::cout << "Altura: " << of1.getAltura() << "m\n";
    std::cout << "Peso: " << of1.getPeso() << "kg\n\n";

    return 0;
}
