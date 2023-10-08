#ifndef CASA_H
#define CASA_H

#include "Imovel.h"


class Casa : public Imovel{
    int numPavimentos;
    int numQuartos;
    double areaConstruida;

    public:
        //-------CONSTRUTORES-------
        Casa();
        Casa(Endereco endereco, tNegocio negocio, double valor, double area, double areaC, int nQrts, int nPvs);


        //-------GETS E SETS--------
        //-->Numero de Pavimentos
        int getNumPav();
        void setNumPav(int nPav);

        //-->Numero de Quartos
        int getNumQuartos();
        void setNumQuartos(int nQrts);

        //-->Area Construida
        double getAreaConstruida();
        void setAreaConstruida(double area);



        //--------DESCRICAO---------
        std::string getDescricao();
        std::string getDescricaoPure();
};

#endif // CASA_H
