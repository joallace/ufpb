#include <iostream>
#include "TestaValidaNumero.h"

int main(){
    int num;
    TestaValidaNumero testador;

    try{
        std::cin >> num;
        testador.validaNumero(num);
    }
    catch(ValorAbaixoException &excecao){
        std::cout << "Valor abaixo" << "\n";
    }
    catch(ValorAcimaException &excecao){
        std::cout << "Valor acima" << "\n";
    }
    catch(ValorMuitoAcimaException &excecao){
        std::cout << "Valor muito acima" << "\n";
    }

    return 0;

}

