#include <iostream>
#include "Empregado.cpp"

int main(){
    Empregado empregado1 = Empregado("Lucas Wanderley", " Silva Medeiros", 897.33);
    Empregado empregado2 = Empregado("Mauro Fernando", " de Maciel da Costa", 1245.97);

    std::cout<<"Empregado: " << empregado1.getNome() << empregado1.getSobrenome() << std::endl;
    std::cout<<"Salario anual: " << empregado1.getSalario()*12<<std::endl;
    empregado1.setSalario(empregado1.getSalario() + (empregado1.getSalario()/10));
    std::cout<<"Novo salario anual: " << empregado1.getSalario()*12<<std::endl;

    std::cout<<std::endl;
    std::cout<<"Empregado: " << empregado2.getNome() << empregado2.getSobrenome() << std::endl;
    std::cout<<"Salario anual: " << empregado2.getSalario()*12<<std::endl;
    empregado2.setSalario(empregado2.getSalario() + (empregado2.getSalario()/10));
    std::cout<<"Novo salario anual: " << empregado2.getSalario()*12<<std::endl;

    return 0;
}
