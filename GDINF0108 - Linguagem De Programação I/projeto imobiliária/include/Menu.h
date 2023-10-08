#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "SistemaImobiliaria.h"


class Menu{
    SistemaImobiliaria *imobiliaria;
    public:
        Menu(SistemaImobiliaria *imobiliaria);

        //Metodos genericos para imoveis
            Endereco getEndereco();
            tNegocio getNegocio();
            double getValor(tNegocio negocio);

        //Metodos especificos de cada imovel
            void getCasa(int *numQuartos, int *numPavimentos, double *areaConstruida, double *area);
            void getApartamento(double *valorCondominio, int *numQuartos, int *vagasGaragem, std::string *posicao, double *area);
            void getTerreno(double *area);


        //Metodos do menu
            //Controle do vetor de imoveis
            void cadastro();
            void remover();
            void editar();

            //Busca e consulta
            void consulta();
            void busca();
            void buscar();

            //Navegacao
            void confirmaSaida();
            void principal();
};

#endif // MENU_H
