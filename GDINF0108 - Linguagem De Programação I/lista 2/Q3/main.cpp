#include <iostream>
#include "Assalariado.cpp"
#include "Horista.cpp"
#include "SistemaGerenciaFolha.cpp"

int main(){
    SistemaGerenciaFolha sistema = SistemaGerenciaFolha();
    Assalariado a1 = Assalariado("Lindimaria", "20191", 894.37);
    Horista h1 = Horista("Itamar", "20192" , 10);

    h1.setHoras(42);

    sistema.setFuncionarios(&a1);
    sistema.setFuncionarios(&h1);

    std::cout << "Salario de funcionario matricula " << a1.getMatricula() << ": " << sistema.consultaSalarioFuncionario(a1.getMatricula()) << "\n";
    std::cout << "Salario de funcionario matricula " << h1.getMatricula() << ": " << sistema.consultaSalarioFuncionario(h1.getMatricula()) << "\n";

    std::cout << "Total da folha: R$"<< sistema.calculaValorTotalFolha() << "\n";

    return 0;
}
