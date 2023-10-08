#ifndef SISTEMAIMOBILIARIA_H
#define SISTEMAIMOBILIARIA_H

#include <fstream>
#include <algorithm>
#include <vector>
#include "conio.h"

#include "Casa.h"
#include "Apartamento.h"
#include "Terreno.h"

class SistemaImobiliaria
{
    std::vector <Imovel*> imoveis;

    public:
        SistemaImobiliaria();

        //Metodos de controle do vetor de imoveis
            void addImovel(Imovel *imovel);
            void removeImovel(int i);

            void editarImovel(Endereco endereco, int i),
                 editarImovel(tNegocio negocio, int i),
                 editarImovel(double valor, int i);

            void editarCasa(int numQuartos, int numPavimentos, double areaConstruida, double area, int i),
                 editarApartamento(double valorCondominio, int numQuartos, int vagasGaragem, std::string posicao, double area, int i),
                 editarTerreno(double area, int i);

        //Metodos de retorno
            std::string getImoveis(),
                        getImoveis(tTipo tipo),
                        getImoveis(tNegocio negocio);

            std::string buscarImovel(std::string local, bool ehCidade),
                        buscarImovel(double valorExigido, bool ehMaior);

            tTipo getTipo(int i);
            tNegocio getNegocio(int i);
            int getQntdImoveis();

         //Metodos de Arquivo
            void salvarImoveis();
            void lerImoveis();

};

#endif // SISTEMAIMOBILIARIA_H
