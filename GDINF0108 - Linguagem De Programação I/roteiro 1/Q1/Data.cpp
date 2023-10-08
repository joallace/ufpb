#include "Data.h"

void Data::avancarDia(){
    switch(mes){
        case 1:
            if(dia < 31)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 2:
            if(dia < 28)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 3:
            if(dia < 31)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 4:
            if(dia < 30)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 5:
            if(dia < 31)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 6:
            if(dia < 30)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 7:
            if(dia < 31)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 8:
            if(dia < 31)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 9:
            if(dia < 30)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 10:
            if(dia < 31)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 11:
            if(dia < 30)
                dia++;
            else{
                mes++;
                dia = 1;
            }
            break;

        case 12:
            if(dia < 31)
                dia++;
            else{
                ano++;
                mes = 1;
                dia = 1;
            }
            break;
    }
}

int Data::getDia(){
    return dia;
}

int Data::getMes(){
    return mes;
}

int Data::getAno(){
    return ano;
}

void Data::setDia(int dia){
    if(dia > 0 && dia <= 31)
        this->dia = dia;
    else
        this->dia = 1;
}

void Data::setMes(int mes){
    if(mes > 0 && mes <= 12)
        this->mes = mes;
    else
        this->mes = 1;
}

void Data::setAno(int ano){
    this->ano = ano;
}

Data::Data(int dia, int mes, int ano){
    setDia(dia);
    setMes(mes);
    setAno(ano);
}
