#ifndef EMPREGADO_DEF
#define EMPREGADO_DEF
#include <string>

class Empregado{
    std::string nome;
    std::string sobrenome;
    double salario;

    public:
        Empregado(std::string, std::string, double);

        std::string getNome();
        std::string getSobrenome();
        double getSalario();

        void setNome(std::string);
        void setSobrenome(std::string);
        void setSalario(double);
};

#endif // EMPREGADO_DEF
