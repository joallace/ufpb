#include "Relogio.h"

void Relogio::setHorario(int hora, int minuto, int segundo){
    this->hora = hora;
    this->minuto = minuto;
    this->segundo = segundo;
}


int Relogio::getHora(){
    return hora;
}

int Relogio::getMinuto(){
    return minuto;
}

int Relogio::getSegundo(){
    return segundo;
}

void Relogio::avancarHorario(){
    if(segundo < 59)
        segundo++;
    else{
        segundo = 0;
        if(minuto < 59)
            minuto++;
        else{
            minuto = 0;
            if(hora < 23)
                hora++;
            else
                hora = 0;
        }
    }
}
