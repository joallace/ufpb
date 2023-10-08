#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include "Relogio.cpp"

int main(){
    int hora, minuto, segundo;
    time_t tempo, tInicial;
    tempo = time(NULL);
    tInicial = tempo;

    std::cout << "Insira a hora:" << std::endl;
    std::cin >> hora;

    std::cout << "Insira a minuto:" << std::endl;
    std::cin >> minuto;

    std::cout << "Insira a segundo:" << std::endl;
    std::cin >> segundo;

    Relogio relogio;
    relogio.setHorario(hora, minuto, segundo);

    while(true){
        tInicial = tempo;
        tempo = time(NULL);
        if((tempo - tInicial) == 1){
            relogio.avancarHorario();
            system("cls");
            std::cout << relogio.getHora() << ":" << relogio.getMinuto() << ":" << relogio.getSegundo() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
