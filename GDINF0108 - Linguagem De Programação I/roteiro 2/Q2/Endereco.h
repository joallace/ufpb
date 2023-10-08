#ifndef ENDERECO_H
#include <string>

class Endereco{
    std::string rua,
                bairro,
                cidade,
                estado,
                numero,
                cep;

    public:
        Endereco();
        Endereco(std::string rua, std::string bairro, std::string cidade,
                 std::string estado, std::string numero, std::string cep);

        std::string toString();
};

#endif // ENDERECO_H
