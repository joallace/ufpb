#ifndef PESSOA_H
#include "Endereco.cpp"

class Pessoa{
    std::string nome,
           telefone;
    Endereco endereco;

    public:
        Pessoa(std::string nome);
        Pessoa(std::string nome, std::string telefone, Endereco endereco);

        std::string getNome();
        void setTelefone(std::string telefone);
        std::string getTelefone();
        void setEndereco(Endereco endereco);
        Endereco getEndereco();
        std::string toString();

};

#endif // PESSOA_H
