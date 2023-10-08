#include <iostream>
#include <stdlib.h>
#include "Televisao.cpp"

int main(){
    Televisao tv = Televisao();
    int canal;
    char opcao[3];

    std::cout << "TV LIGADA!!!" << std::endl;

    while(1){
        std::cin >> opcao;
        system("cls");
        if(opcao[1] == '+' || opcao[1] == '-'){
            if(opcao[0] == 'c')
                tv.uCanal(opcao[1]);
                if(opcao[2] == '+')
                    while(1)
                        std::cout << "C++ KKKKKKKKKK";
            if(opcao[0] == 'v')
                tv.uVolume(opcao[1]);
        }else{
            canal = atoi(opcao);
            tv.setCanal(canal);
        }

        std::cout << "Canal: " << tv.getCanal() << std::endl;
        std::cout << "Volume: " << tv.getVolume() << std::endl;
    }
    return 0;
}
