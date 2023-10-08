#include "SistemaImobiliaria.h"

//FUNCAO USADA PARA A COMPARACAO DE STRINGS
std::string str_toupper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){return std::toupper(c);});
    return s;
}

SistemaImobiliaria::SistemaImobiliaria(){}

//Metodos de controle do vetor de imoveis
void SistemaImobiliaria::addImovel(Imovel *imovel){
    imoveis.push_back(imovel);
}

void SistemaImobiliaria::removeImovel(int i){
    imoveis.erase(imoveis.begin() + i);
}

void SistemaImobiliaria::editarImovel(Endereco endereco, int i){
    imoveis[i]->setEndereco(endereco);
}

void SistemaImobiliaria::editarImovel(tNegocio negocio, int i){
    imoveis[i]->setNegocio(negocio);
}

void SistemaImobiliaria::editarImovel(double valor, int i){
    imoveis[i]->setValor(valor);
}

void SistemaImobiliaria::editarCasa(int numQuartos, int numPavimentos, double areaConstruida, double area, int i){
    Casa *c = (Casa*)imoveis[i];

    c->setNumQuartos(numQuartos);
    c->setNumPav(numPavimentos);
    c->setAreaConstruida(areaConstruida);
    c->setArea(area);
}

void SistemaImobiliaria::editarApartamento(double valorCondominio, int numQuartos, int vagasGaragem, std::string posicao, double area, int i){
    Apartamento *a = (Apartamento*)imoveis[i];

    a->setValorCond(valorCondominio);
    a->setNumQuartos(numQuartos);
    a->setVagasGaragem(vagasGaragem);
    a->setPosicao(posicao);
    a->setArea(area);
}


void SistemaImobiliaria::editarTerreno(double area, int i){
    imoveis[i]->setArea(area);
}
//Metodos de controle do vetor de imoveis



//Metodos de retorno
std::string  SistemaImobiliaria::getImoveis(){
    std::string total = "";

    for(unsigned int i=0; i < imoveis.size(); i++)
        total = total + "--------------========Imovel n" + std::to_string(i+1) +
        "========------------\n" + imoveis[i]->getDescricao() + "\n\n" ;

    return total;
}

std::string  SistemaImobiliaria::getImoveis(tTipo tipo){
    std::string total = "";

    for(unsigned int i=0; i < imoveis.size(); i++){
        if(imoveis[i]->getTipo() == tipo){
            total = total + "--------------========Imovel n" + std::to_string(i+1) +
            "========------------\n" + imoveis[i]->getDescricao() + "\n\n" ;
        }
    }
    return total;
}

std::string  SistemaImobiliaria::getImoveis(tNegocio negocio){
    std::string total = "";

    for(unsigned int i=0; i < imoveis.size(); i++)
        if(imoveis[i]->getNegocio() == negocio){
            total = total + "--------------========Imovel n" + std::to_string(i+1) +
            "========------------\n" + imoveis[i]->getDescricao() + "\n\n" ;
        }
    return total;
}

std::string SistemaImobiliaria::buscarImovel(std::string local, bool ehCidade){
    std::string total = "";

    if(ehCidade){
            for(unsigned int i=0; i < imoveis.size(); i++){
                if(str_toupper(imoveis[i]->getEnderecoPure().cidade).find(str_toupper(local)) == 0){
                    total = total + "--------------========Imovel n" + std::to_string(i+1) +
                    "========------------\n" + imoveis[i]->getDescricao() + "\n\n" ;
                }
            }

    }else{
        for(unsigned int i=0; i < imoveis.size(); i++){
                if(str_toupper(imoveis[i]->getEnderecoPure().bairro).find(str_toupper(local)) == 0){
                    total = total + "--------------========Imovel n" + std::to_string(i+1) +
                    "========------------\n" + imoveis[i]->getDescricao() + "\n\n" ;
                }
            }
    }
return total;

}

std::string SistemaImobiliaria::buscarImovel(double valorExigido, bool ehMaior){
    std::string total = "";

    if(ehMaior){
        for(unsigned int i=0; i < imoveis.size(); i++){
            if(imoveis[i]->getValor() >= valorExigido){
                total = total + "--------------========Imovel n" + std::to_string(i+1) +
                "========------------\n" + imoveis[i]->getDescricao() + "\n\n" ;
            }
        }
    }else{
        for(unsigned int i=0; i < imoveis.size(); i++){
            if(imoveis[i]->getValor() <= valorExigido){
                total = total + "--------------========Imovel n" + std::to_string(i+1) +
                "========------------\n" + imoveis[i]->getDescricao() + "\n\n" ;
            }
        }

    }
    return total;
}

tTipo SistemaImobiliaria::getTipo(int i){
    return imoveis[i]->getTipo();
}

tNegocio SistemaImobiliaria::getNegocio(int i){
    return imoveis[i]->getNegocio();
}

int SistemaImobiliaria::getQntdImoveis(){
    return imoveis.size();
}
//Metodos de retorno


//Metodos de Arquivo
void SistemaImobiliaria::salvarImoveis(){
    std::ofstream dados;

    dados.open("dados.txt", std::ios::out);

    for(unsigned int i=0; i<imoveis.size(); i++){
        dados << imoveis[i]->getDescricaoPure();
    }
    dados.close();
}

void SistemaImobiliaria::lerImoveis(){
    std::ifstream dados;

    std::string rua,
                numero,
                bairro,
                cidade,
                cep;

    std::string auxStr;
    int auxInt;
    double auxDbl;

    dados.open("dados.txt", std::ios::in);

    if(dados.is_open())
        while(dados.peek()!=EOF){
            getline(dados, auxStr);
            if(!auxStr.compare("CASA")){
                Casa *c = new Casa();

                getline(dados, auxStr);
                if(!auxStr.compare("VENDA"))
                    c->setNegocio(VENDA);
                else
                    c->setNegocio(ALUGUEL);

                getline(dados, auxStr);
                auxDbl = std::stod(auxStr);
                c->setValor(auxDbl);

                getline(dados, cep);
                getline(dados, cidade);
                getline(dados, bairro);
                getline(dados, rua);
                getline(dados, numero);
                Endereco endereco = Endereco(rua, bairro, cidade, cep, numero);
                c->setEndereco(endereco);

                getline(dados, auxStr);
                auxInt = std::stoi(auxStr);
                c->setNumQuartos(auxInt);

                getline(dados, auxStr);
                auxInt = std::stoi(auxStr);
                c->setNumPav(auxInt);

                getline(dados, auxStr);
                auxDbl = std::stod(auxStr);
                c->setAreaConstruida(auxDbl);

                getline(dados, auxStr);
                auxDbl = std::stod(auxStr);
                c->setArea(auxDbl);

                addImovel(c);
            }

            else if(!auxStr.compare("APARTAMENTO")){
                Apartamento *a = new Apartamento();

                getline(dados, auxStr);
                if(!auxStr.compare("VENDA"))
                    a->setNegocio(VENDA);
                else
                    a->setNegocio(ALUGUEL);

                getline(dados, auxStr);
                auxDbl = std::stod(auxStr);
                a->setValor(auxDbl);

                getline(dados, cep);
                getline(dados, cidade);
                getline(dados, bairro);
                getline(dados, rua);
                getline(dados, numero);
                Endereco endereco = Endereco(rua, bairro, cidade, cep, numero);
                a->setEndereco(endereco);

                getline(dados, auxStr);
                auxInt = std::stoi(auxStr);
                a->setNumQuartos(auxInt);

                getline(dados, auxStr);
                auxInt = std::stoi(auxStr);
                a->setVagasGaragem(auxInt);

                getline(dados, auxStr);
                auxDbl = std::stod(auxStr);
                a->setValorCond(auxDbl);

                getline(dados, auxStr);
                a->setPosicao(auxStr);

                getline(dados, auxStr);
                auxDbl = std::stod(auxStr);
                a->setArea(auxDbl);

                addImovel(a);
            }
            else if(!auxStr.compare("TERRENO")){
                Terreno *t = new Terreno();

                getline(dados, auxStr);

                if(!auxStr.compare("VENDA"))
                    t->setNegocio(VENDA);
                else
                    t->setNegocio(ALUGUEL);

                getline(dados, auxStr);
                auxDbl = std::stod(auxStr);
                t->setValor(auxDbl);

                getline(dados, cep);
                getline(dados, cidade);
                getline(dados, bairro);
                getline(dados, rua);
                getline(dados, numero);
                Endereco endereco = Endereco(rua, bairro, cidade, cep, numero);
                t->setEndereco(endereco);

                getline(dados, auxStr);
                auxDbl = std::stod(auxStr);
                t->setArea(auxDbl);

                addImovel(t);
            }
        }
    dados.close();
}
//Metodos de Arquivo
