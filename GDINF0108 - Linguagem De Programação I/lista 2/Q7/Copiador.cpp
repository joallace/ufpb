#include <iostream>
#include <fstream>
#include <string>

int main(){
    std::ifstream original;
    std::ofstream copia;

    std::string aux;
    unsigned int i = 1;

    original.open("teste.txt", std::ios::in);
    copia.open("teste_bkp.txt", std::ios::out);

    if(copia.is_open() && original.is_open()){
        while(!original.eof()){
            getline(original, aux);
            std::cout << "Rodada "<< i++ << ": " << aux << "\n";
            copia << aux + "\n";;
        }
    }
    else{
        std::cout << "Não foi possivel abrir arquivo\n";
        return -1;
    }

    original.close();
    copia.close();

    std::cout << "Copia realizada com sucesso!\n";
    return 0;
}
