#include "Terreno.h"

Terreno::Terreno(): Imovel(){
    tipo = TERRENO;
}

Terreno::Terreno(Endereco endereco, tNegocio negocio, double valor, double area): Imovel(endereco, negocio, valor, area){
    tipo = TERRENO;
}

std::string Terreno::getDescricao(){
    return "Tipo de Imovel: Terreno\n" +
           Imovel::getDescricao() + "\n" +

           "\nCaracteristicas do Terreno\n" +
           "\t->Area total: " + std::to_string(getArea()) + "\n";
}


std::string Terreno::getDescricaoPure(){
    return "TERRENO\n" +
           Imovel::getDescricaoPure() +
           std::to_string(getArea()) + "\n\n";
}
