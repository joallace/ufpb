#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <string>

class Funcionario{
    protected:
        std::string nome,
                    matricula;
    public:
        bool atividade;

        std::string getNome(),
                    getMatricula();
        void setNome(std::string),
             setMatricula(std::string);

        virtual double calculaSalario() = 0;

        Funcionario(std::string, std::string);

};

#endif // FUNCIONARIO_H
