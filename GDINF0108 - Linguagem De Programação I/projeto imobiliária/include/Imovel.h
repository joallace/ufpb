#ifndef IMOVEL_H
#define IMOVEL_H

#include "Endereco.h"

typedef enum {VENDA, ALUGUEL} tNegocio;

typedef enum {CASA, APARTAMENTO, TERRENO} tTipo;

class Imovel{
    protected:
        double valor,
               area;
        Endereco endereco;
        tTipo tipo;
        tNegocio negocio;

    public:
        //-------CONSTRUTORES-------
        Imovel();
        Imovel(Endereco endereco, tNegocio negocio, double valor, double area);


        //-------GETS E SETS--------
        //-->Valor
        double getValor();
        void setValor(double valor);


        //-->Endereco
        Endereco getEnderecoPure();
        std::string getEndereco();
        void setEndereco(Endereco endereco);


        //-->Area
        double getArea();
        void setArea(double area);

        //-->Tipo
        tTipo getTipo();
        void setTipo(tTipo tipo);

        //-->Negocio
        tNegocio getNegocio();
        void setNegocio(tNegocio negocio);

        //---------DESCRICAO---------
        virtual std::string getDescricao();
        virtual std::string getDescricaoPure();
};

#endif // IMOVEL_H
