#include <iostream>
#include "TrabalhadorAssalariado.cpp"
#include "TrabalhadorPorHora.cpp"


int main(){
    TrabalhadorAssalariado t1 = TrabalhadorAssalariado("Clodoaldo", 2325.40);
    TrabalhadorPorHora t2 = TrabalhadorPorHora("Rosivaldo", 37.50);

        std::cout << t1.calcularPagamentoSemanal() << std::endl;
        std::cout << t2.calcularPagamentoSemanal(25) << std::endl;
        std::cout << t2.calcularPagamentoSemanal(45) << std::endl;
    return 0;
}
