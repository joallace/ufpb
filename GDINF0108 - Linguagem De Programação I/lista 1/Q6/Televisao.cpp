#include "Televisao.h"

int Televisao::getVolume(){
    return volume;
}

int Televisao::getCanal(){
    return canal;
}

void Televisao::setCanal(int canal){
    if(canal > 0 && canal < 100)
        this->canal = canal;
}

void Televisao::uVolume(char sinal){
    if(sinal == '+' && volume < 100)
        volume++;
    else
        if(sinal == '-' && volume > 0)
            volume--;
}

void Televisao::uCanal(char sinal){
    if(sinal == '+' && canal < 99)
        canal++;
    else
        if(sinal == '-' && canal > 0)
            canal--;
}

