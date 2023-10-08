#include <iostream>
#include "Funcionario.cpp"
#include "Consultor.cpp"

int main(){
    Funcionario funcionario1 = Funcionario("Lucas Wanderley", "2018002854", 897.33);
    Consultor consultor1 = Consultor("Mauro Fernando", "2018002856", 1245.97);

    /*
    consultor1.setNome("Mauro Fernando");
    consultor1.setMatricula("2018002856");
    consultor1.setSalario(1245.97);
    */

    std::cout<<"Funcionario: " << funcionario1.getNome() << std::endl;
    std::cout<<"Matricula: " << funcionario1.getMatricula() << std::endl;
    std::cout<<"Salario: " << funcionario1.getSalario()<<std::endl;
    funcionario1.setSalario(funcionario1.getSalario() + (funcionario1.getSalario()/10));
    std::cout<<"Novo salario: " << funcionario1.getSalario()<<std::endl;

    std::cout<<std::endl;
    std::cout<<"Consultor: " << consultor1.getNome() << std::endl;
    std::cout<<"Matricula: " << consultor1.getMatricula() << std::endl;
    std::cout<<"Salario: " << consultor1.getSalario()<<std::endl;
    std::cout<<"Novo salario: " << consultor1.getSalario(0.12)<<std::endl;

    return 0;
}
