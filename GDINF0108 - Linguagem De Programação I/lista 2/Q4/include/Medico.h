#ifndef MEDICO_H
#define MEDICO_H

#include<string>

class Medico
{
    std::string nome;
    std::string altura;
    std::string peso;
    std::string nomeEspecialidade;

    public:
        Medico(std::string nome, std::string altura, std::string peso);

        std::string getNome();
        void setNome(std::string val);

        std::string getAltura();
        void setAltura(std::string val);

        std::string getPeso();
        void setPeso(std::string val);

        std::string getEspecialidade();
        void setEspecialidade(std::string val);

        virtual std::string atendimento() = 0;
};

#endif // MEDICO_H
