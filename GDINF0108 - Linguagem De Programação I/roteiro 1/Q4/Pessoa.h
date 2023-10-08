#ifndef PESSOA_DEF
#define PESSOA_DEF
#include <string>

class Pessoa{
    std::string nome;
    int idade;
    std::string telefone;

    public:
        Pessoa(std::string);
        Pessoa(std::string, int, std::string);

        std::string getNome();
        int getIdade();
        std::string getTelefone();

        void setNome(std::string);
        void setIdade(int);
        void setTelefone(std::string);
};

#endif // PESSOA_DEF
