#include <iostream>
#include "Triangulo.cpp"
#include "Quadrado.cpp"
#include "Circulo.cpp"

int main(){
    Triangulo triangulo = Triangulo();
    Circulo circulo = Circulo();
    Quadrado quadrado = Quadrado();

    std::cout << "Area do " << circulo.getNome() << " raio 2: " << circulo.calcularArea(2) << std::endl;
    std::cout << "Area do " << triangulo.getNome() << " de altura 4 e base 2: " << triangulo.calcularArea(2, 4) << std::endl;
    std::cout << "Area do " << quadrado.getNome() << " de lado 2: " << quadrado.calcularArea(2) << std::endl;

}
