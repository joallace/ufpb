#ifndef TERRENO_H
#define TERRENO_H

#include "Imovel.h"


class Terreno : public Imovel{
    public:
        //-------CONSTRUTORES-------
        Terreno();
        Terreno(Endereco endereco, tNegocio negocio, double valor, double area);


        //--------DESCRICAO---------
        std::string getDescricao();
        std::string getDescricaoPure();
};

#endif // TERRENO_H
