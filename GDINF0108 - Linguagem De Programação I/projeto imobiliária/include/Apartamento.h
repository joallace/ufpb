#ifndef APARTAMENTO_H
#define APARTAMENTO_H

#include "Imovel.h"


class Apartamento : public Imovel{
    std::string posicao;
    int numQuartos;
    double valorCondominio;
    int vagasGaragem;

    public:
        //-------CONSTRUTORES-------
        Apartamento();
        Apartamento(Endereco endereco, tNegocio negocio, double valor, double area, double valC, int nQrts, int vagas, std::string posicao);


        //-------GETS E SETS--------
        //-->Posicao
        std::string getPosicao();
        void setPosicao(std::string posicao) ;

        //-->Numero de Quartos
        int getNumQuartos();
        void setNumQuartos(int nQrts);

        //-->Valor do Condominio
        double getValorCond() ;
        void setValorCond(double valC) ;

        //-->Vagas na Garagem
        int getVagasGaragem() ;
        void setVagasGaragem(int vagas) ;



        //--------DESCRICAO---------
        std::string getDescricao();
        std::string getDescricaoPure();
};

#endif // APARTAMENTO_H
