#ifndef ENDERECO_H
#define ENDERECO_H

#ifndef STRING_I
#define STRING_I
#include <string>
#endif //STRING_I

class Endereco{
    public:
    Endereco(std::string rua,std::string bairro,std::string cidade,std::string cep,std::string numero);
    Endereco();

    std::string rua,
           bairro,
           cidade,
           cep,
           numero;
};

#endif // ENDERECO_H
