#include "Casa.h"

Casa::Casa():Imovel(){
    setNumPav(0);
    setNumQuartos(0);
    setAreaConstruida(0);
    tipo = CASA;
}

Casa::Casa(Endereco endereco, tNegocio negocio, double valor, double area,
           double areaC, int nQrts, int nPvs) : Imovel(endereco, negocio, valor, area){
    setNumPav(nPvs);
    setNumQuartos(nQrts);
    setAreaConstruida(areaC);
    tipo = CASA;
}


std::string Casa::getDescricao(){
    return "Tipo de Imovel: Casa\n" +
           Imovel::getDescricao() + "\n" +

           "\nCaracteristicas da Casa\n" +
           "\t->Quantidade de quartos: " + std::to_string(numQuartos) + "\n" +
           "\t->Quantidade de pavimentos: " + std::to_string(numPavimentos) + "\n" +
           "\t->Area construida: " + std::to_string(areaConstruida) + "\n" +
           "\t->Area total: " + std::to_string(getArea()) + "\n";
}

std::string Casa::getDescricaoPure(){
    return "CASA\n" +
           Imovel::getDescricaoPure() +
           std::to_string(numQuartos) + "\n" +
           std::to_string(numPavimentos) + "\n" +
           std::to_string(areaConstruida) + "\n" +
           std::to_string(getArea()) + "\n\n";
}


int Casa::getNumPav()
{
    return numPavimentos;
}

void Casa::setNumPav(int nPav)
{
    numPavimentos = nPav;
}

int Casa::getNumQuartos()
{
    return numQuartos;
}

void Casa::setNumQuartos(int nQrts)
{
    numQuartos = nQrts;
}

double Casa::getAreaConstruida()
{
    return areaConstruida;
}

void Casa::setAreaConstruida(double area)
{
    areaConstruida = area;
}
